#include "response.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#define IMSI "1234567890"
#define IMEI "0987654321"

void generate_response(const char *command, char *response, size_t response_len) {
	
	cJSON *json = cJSON_CreateObject();

	if(strncmp(command, "/imsi", 5) == 0) {
		cJSON_AddStringToObject(json, "command", "/imsi");
		cJSON_AddStringToObject(json, "IMSI", IMSI);
	} else if(strncmp(command, "/imei", 5) == 0) {
		cJSON_AddStringToObject(json, "command", "/imei");
		cJSON_AddStringToObject(json, "IMEI", IMEI);
	} else {
		cJSON_AddStringToObject(json, "error", "unknown_command");
	}

	//convert JSON object to string
	char *json_string = cJSON_PrintUnformatted(json);
	strncpy(response, json_string, response_len - 1);
	response[response_len - 1] = '\0'; //Ensuring null termination

	//Clean up 
	free(json_string);
	cJSON_Delete(json);
}

