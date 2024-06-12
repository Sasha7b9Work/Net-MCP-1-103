// 2022/04/27 11:48:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/Modules/HC12/HC12.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Modules/BME280/BME280.h"
#include "Hardware/Modules/CG-Anem/CG-Anem.h"
#include "Hardware/Modules/BH1750/BH1750.h"
#include "Hardware/CDC/CDC.h"
#include "Hardware/Modules/ST7735/ST7735.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Display/Display.h"
#include "Hardware/Keyboard.h"
#include "Storage/Measures.h"


namespace Device
{
    static void ProcessMeasure(const Measure &, uint time);
}


void Device::Init()
{
    HAL::Init();

    ST7735::Init();

    BME280::Init();

    HC12::Init();

#ifdef TYPE_1
    CG_Anem::Init();
#endif

    BH1750::Init();

    Keyboard::Init();

    InterCom::SetDirection((Direction::E)(Direction::CDC | Direction::HC12 | Direction::Display));
}


void Device::Update()
{
    Measure temp(Measure::Temperature);
    Measure pressure(Measure::Pressure);
    Measure humidity(Measure::Humidity);
    Measure velocity(Measure::Velocity);
    Measure illumination(Measure::Illumination);

    uint time = TIME_MS;

    if (BME280::GetMeasures(&temp, &pressure, &humidity))
    {
        ProcessMeasure(temp, time);
        ProcessMeasure(pressure, time);
        ProcessMeasure(humidity, time);
    }

#ifdef TYPE_1

    if (CG_Anem::GetMeasure(&velocity))
    {
        ProcessMeasure(velocity, time);
    }
#endif

    if (BH1750::GetMeasure(&illumination))
    {
        ProcessMeasure(illumination, time);
    }

    Keyboard::Update();

    Display::Update();
}


void Device::ProcessMeasure(const Measure &measure, uint time)
{
    if (measure.correct)
    {
        InterCom::Send(measure, time);
    }
}
