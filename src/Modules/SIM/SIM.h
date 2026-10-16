#pragma once

bool initSIM();
bool SIM_ModuleTest();
bool SIM_SIMCardTest();
bool SIM_NetworkTest(uint32_t timeout = 30000);
int SIM_GetSignalLevel();
bool sendSMS(const char *phoneNumber, const String &message);
bool MakeCall(const char* number);

extern char phoneNumber[12];