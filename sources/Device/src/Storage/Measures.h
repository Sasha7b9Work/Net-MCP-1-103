// 2023/06/12 16:46:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
//#include "Display/Display.h"


struct Measure
{
    enum E
    {
        Temperature,    // Температура
        Pressure,       // Давление
        Humidity,       // Влажность
        DewPoint,       // Точка росы
        Velocity,       // Скорость воздуха
        Latitude,       // Широта
        Longitude,      // Долгота
        Altitude,       // Высота
        Azimuth,        // Азимут - угол от направления на север
        Illumination,
        Count
    };

    double value;

    // У первых NumAlarmed() измерений нужно контролировать выход за границы
    static int NumAlarmed() { return 5; }

    void Clear()
    {
        type = Count;
        correct = false;
        value = (double)ERROR_VALUE_FLOAT;
    }

    double GetDouble() const
    {
        return value;
    }

    E GetType() const
    {
        return type;
    }

    bool IsEnabled() const;

    void Set(E _name, float _value)
    {
        Set(_name, (double)_value);
    }

    void Set(E _name, double _value)
    {
        type = _name;
        SetDouble(_value);
        correct = true;
    }

    bool correct;

    Measure(E v) : value(0.0), correct(false), type(v) { }

private:

    void SetDouble(float _value)
    {
        SetDouble((double)_value);
    }

    void SetDouble(double _value)
    {
        value = _value;
    }

    E type;
};


namespace Measures
{
    // Фиксирует последние измерения на экране
    void SetFixed(bool fixed);
    bool IsFixed();
}
