#pragma once

#define INDICATOR_LED 13

void FssHandler();

void RssHandler();

void Reset();

void ReceiveCommand();

void Stby();

void StartMeasuring();

void SendSpeed();

void ResetDebouncingTriggers();

void SetTestSpeed();
