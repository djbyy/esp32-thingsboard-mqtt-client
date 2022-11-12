// Copyright 2022 liangzhuzhi2020@gmail.com, https://github.com/liang-zhu-zi/esp32-thingsboard-mqtt-client
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _TBC_MQTT_HETLPER_INTERNAL_H_
#define _TBC_MQTT_HETLPER_INTERNAL_H_

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "sys/queue.h"
#include "esp_err.h"

// #include "tbc_utils.h"
#include "tbc_transport_config.h"
#include "tbc_transport_storage.h"

#include "tbc_mqtt.h"
// #include "tbc_mqtt_helper.h"

#include "timeseries_data_helper.h"
#include "client_attribute_helper.h"
#include "shared_attribute_observer.h"
#include "attributes_request_observer.h"
#include "server_rpc_observer.h"
#include "client_rpc_observer.h"
#include "provision_observer.h"
#include "ota_update_observer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ThingsBoard MQTT Client Helper 
 */
typedef struct tbcmh_client
{
     // TODO: add a lock???
     // create & destroy
     tbcm_handle_t tbmqttclient;
     QueueHandle_t _xQueue;
     esp_timer_handle_t respone_timer;   // /*!< timer for checking response timeout */

     // modify at connect & disconnect
     tbc_transport_storage_t config;
     void *context;                          /*!< Context parameter of the below two callbacks */
     tbcmh_on_connected_t on_connected;      /*!< Callback of connected ThingsBoard MQTT */
     tbcmh_on_disconnected_t on_disconnected;/*!< Callback of disconnected ThingsBoard MQTT */

     // tx & rx msg
     SemaphoreHandle_t _lock;
     LIST_HEAD(tbcmh_tsdata_list, tbcmh_tsdata) tsdata_list;                              /*!< telemetry time-series data entries */
     LIST_HEAD(tbcmh_clientattribute_list, tbcmh_clientattribute) clientattribute_list;   /*!< client attributes entries */
     LIST_HEAD(tbcmh_sharedattribute_list, tbcmh_sharedattribute) sharedattribute_list;   /*!< shared attributes entries */
     LIST_HEAD(tbcmh_attributesrequest_list, tbcmh_attributesrequest) attributesrequest_list;  /*!< attributes request entries */
     LIST_HEAD(tbcmh_serverrpc_list, tbcmh_serverrpc) serverrpc_list;  /*!< server side RPC entries */
     LIST_HEAD(tbcmh_clientrpc_list, tbcmh_clientrpc) clientrpc_list;  /*!< client side RPC entries */
     LIST_HEAD(tbcmh_provision_list, tbcmh_provision) provision_list;  /*!< provision entries */
     LIST_HEAD(tbcmh_otaupdate_list, tbcmh_otaupdate) otaupdate_list;    /*!< A device may have multiple firmware */
} tbcmh_t;

#ifdef __cplusplus
}
#endif //__cplusplus

#endif

