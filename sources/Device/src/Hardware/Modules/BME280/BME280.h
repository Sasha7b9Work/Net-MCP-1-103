// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Storage/Measures.h"


namespace BME280
{
    void Init();

    bool GetMeasures(Measure *temp, Measure *pressure, Measure *humidity);
}
