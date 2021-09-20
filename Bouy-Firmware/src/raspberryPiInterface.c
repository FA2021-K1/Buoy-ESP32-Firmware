
#include "raspberryPiInterface.h"
#include "hardwareLayout.h"
#include <Arduino.h>

#define UART_BUF_SIZE 256
static QueueHandle_t uart_queue;

void initRaspPi(struct RaspPi *pi){
    pi->online = false;
    pi->turningOn = false;
    pinMode(PI_RELAY_PIN,OUTPUT);
    digitalWrite(PI_RELAY_PIN,LOW);

    pi->uart_config = malloc(sizeof(uart_config_t));
    pi->uart_config->baud_rate = 115200;
    pi->uart_config->data_bits = UART_DATA_8_BITS;
    pi->uart_config->parity = UART_PARITY_DISABLE;
    pi->uart_config->stop_bits = UART_STOP_BITS_1;
    pi->uart_config->flow_ctrl = UART_HW_FLOWCTRL_DISABLE;

    uart_param_config(PI_UART, pi->uart_config);
    uart_set_pin(PI_UART,U2TXD, U2RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uart_driver_install(PI_UART,UART_BUF_SIZE,UART_BUF_SIZE,20,&uart_queue,0);

    xTaskCreate(UART_ISR_ROUTINE, "UART_ISR_ROUTINE", 2048,NULL,12,NULL);
}

void deinitRaspPi(struct RaspPi *pi){
    free(pi->uart_config);
}

void turnOnPi(struct RaspPi *pi){
    pi->online = false;
    digitalWrite(PI_RELAY_PIN,HIGH);
}

void turnOffPi(struct RaspPi *pi){
    pi->online = false;
    digitalWrite(PI_RELAY_PIN,LOW);
}

static void UART_ISR_ROUTINE(void* pvParameters){
    uart_event_t event;
    size_t buffered_size;
    bool exit_condition = false;
   
    //Infinite loop to run main bulk of task
    while (1) {
     
        //Loop will continually block (i.e. wait) on event messages from the event queue
        if(xQueueReceive(uart_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
         
            //Handle received event
            if (event.type == UART_DATA) {
 
                uint8_t UART2_data[128];
                int UART2_data_length = 0;
                ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, (size_t*)&UART2_data_length));
                UART2_data_length = uart_read_bytes(UART_NUM_2, UART2_data, UART2_data_length, 100);
             
                Serial.println("LEN= ");Serial.println(UART2_data_length);
 
                Serial.print("DATA= ");
                for(byte i=0; i<UART2_data_length;i++) Serial.print((char)UART2_data[i]);
                Serial.println("");
             
            }
           
            //Handle frame error event
            else if (event.type == UART_FRAME_ERR) {
                //TODO...
            }
           
            //Keep adding else if statements for each UART event you want to support
            //else if (event.type == OTHER EVENT) {
                //TODO...
            //}
           
           
            //Final else statement to act as a default case
            else {
                //TODO...
            }      
        }
       
        //If you want to break out of the loop due to certain conditions, set exit condition to true
        if (exit_condition) {
            break;
        }
    }
   
    //Out side of loop now. Task needs to clean up and self terminate before returning
    vTaskDelete(NULL);
}