#include "parse_json.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

void parse_json_data(char *response, size_t response_len){
	logd("Entering into json parser application.");
	cJSON *json = cJSON_Parse(response);
    if (json == NULL) {
		printf("Error parsing JSON response\n");
	} else {
		cJSON *status = cJSON_GetObjectItem(json, "status");
		cJSON *imsi = cJSON_GetObjectItem(json, "imsi");
		cJSON *imei = cJSON_GetObjectItem(json, "imei");

		if (cJSON_IsString(status) && cJSON_IsString(imsi)) {
		printf("Status: %s\n", status->valuestring);
		printf("IMSI: %s\n", imsi->valuestring);
		}

		else if (cJSON_IsString(status) && cJSON_IsString(imei)) {
		printf("Status: %s\n", status->valuestring);
		printf("IMEI: %s\n", imsi->valuestring);
		}
	}
}
