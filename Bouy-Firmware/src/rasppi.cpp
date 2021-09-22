#include <Arduino.h>

#include "ArduinoJson.h"

#include "rasppi.h"
#include "hardwareLayout.h"

#define UART_BUF_SIZE (2048)
static QueueHandle_t uart_queue;
static void UART_ISR_ROUTINE(void *pvParameters);

void init_uart();

RaspPi::RaspPi()
{
    this->_rasppi_status = RaspPiStatus::OFF;

    pinMode(PI_RELAY_PIN, OUTPUT);
    digitalWrite(PI_RELAY_PIN, LOW);

    init_uart();
}

RaspPiStatus RaspPi::get_status()
{
    return this->_rasppi_status;
}

void RaspPi::writeData(std::string json_string)
{
    //TODO
}

void RaspPi::turnOn()
{
    this->_rasppi_status = RaspPiStatus::TURNING_ON;
    digitalWrite(PI_RELAY_PIN, HIGH);
}

void RaspPi::turnOff()
{
    this->_rasppi_status = RaspPiStatus::TURNING_OFF;
    digitalWrite(PI_RELAY_PIN, LOW);
}

void init_uart()
{
    Serial.println("Initializing UART2");
    uart_config_t uart2_configuartion = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
    ESP_ERROR_CHECK(uart_param_config(PI_UART, &uart2_configuartion));

    ESP_ERROR_CHECK(uart_set_pin(PI_UART, U2TXD, U2RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_ERROR_CHECK(uart_driver_install(PI_UART, UART_BUF_SIZE, UART_BUF_SIZE, 20, &uart_queue, 0));

    uart_enable_pattern_det_intr(PI_UART, '+', 2, 9, 0, 0);
    //Reset the pattern queue length to record at most 20 pattern positions.
    uart_pattern_queue_reset(PI_UART, 20);

    xTaskCreate(UART_ISR_ROUTINE, "UART_ISR_ROUTINE", 2048, NULL, 12, NULL);
}

static void UART_ISR_ROUTINE(void *pvParameters)
{
    uart_event_t event;
    bool exit_condition = false;

    uint8_t *dtmp = (uint8_t *)malloc(UART_BUF_SIZE);
    int dtmp_index = 0;

    //Infinite loop to run main bulk of task
    while (1)
    {

        //Loop will continually block (i.e. wait) on event messages from the event queue
        if (xQueueReceive(uart_queue, (void *)&event, (portTickType)portMAX_DELAY))
        {
            int received_data_length = 0;

            //Handle received event
            switch (event.type)
            {
            case UART_DATA:
                ESP_ERROR_CHECK(uart_get_buffered_data_len(PI_UART, (size_t *)&received_data_length));
                received_data_length = uart_read_bytes(PI_UART, dtmp + dtmp_index, received_data_length, 100);

                dtmp_index += received_data_length;
                for (int i = received_data_length; i > 0; i--)
                {
                    if (dtmp[dtmp_index - i] == '\0')
                    {
                        for (byte i = 0; i < dtmp_index; i++)
                            Serial.write(dtmp[i]);

                        dtmp_index = 0;
                        break;
                    }
                }
                break;
            default:
                Serial.println("Error: by RaspPi UART_ISR_ROUTINE: Unexpected UART Event");
                //Keep adding else if statements for each UART event you want to support
                //else if (event.type == OTHER EVENT) {
                //TODO...
                //}

                //Final else statement to act as a default case
                break;
            }
        }

        //If you want to break out of the loop due to certain conditions, set exit condition to true
        if (exit_condition)
        {
            break;
        }
    }
    free(dtmp);

    //Out side of loop now. Task needs to clean up and self terminate before returning
    vTaskDelete(NULL);
}