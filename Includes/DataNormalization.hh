#pragma once
#include <cstdint>
#include <cmath>

struct MPU6050_Data
{
    float Ax;
    float Ay;
    float Az;
    float Gx;
    float Gy;
    float Gz;

    MPU6050_Data(float ax = 0, float ay = 0, float az = 0, float gx = 0, float gy = 0, float gz = 0)
        : Ax(ax), Ay(ay), Az(az), Gx(gx), Gy(gy), Gz(gz)
    {
    }
};

void CalculateMean(MPU6050_Data arr[], uint8_t size, MPU6050_Data &res)
{
    res = MPU6050_Data(); // Initialize result to zero
    for (uint8_t i = 0; i < size; ++i)
    {
        res.Ax += arr[i].Ax;
        res.Ay += arr[i].Ay;
        res.Az += arr[i].Az;
        res.Gx += arr[i].Gx;
        res.Gy += arr[i].Gy;
        res.Gz += arr[i].Gz;
    }

    res.Ax /= size;
    res.Ay /= size;
    res.Az /= size;
    res.Gx /= size;
    res.Gy /= size;
    res.Gz /= size;
}

void CalculateSD(MPU6050_Data arr[], uint8_t size, MPU6050_Data &res)
{
    MPU6050_Data mean;
    CalculateMean(arr, size, mean);

    res = MPU6050_Data(); // Initialize result to zero
    for (uint8_t i = 0; i < size; ++i)
    {
        res.Ax += (arr[i].Ax - mean.Ax) * (arr[i].Ax - mean.Ax);
        res.Ay += (arr[i].Ay - mean.Ay) * (arr[i].Ay - mean.Ay);
        res.Az += (arr[i].Az - mean.Az) * (arr[i].Az - mean.Az);
        res.Gx += (arr[i].Gx - mean.Gx) * (arr[i].Gx - mean.Gx);
        res.Gy += (arr[i].Gy - mean.Gy) * (arr[i].Gy - mean.Gy);
        res.Gz += (arr[i].Gz - mean.Gz) * (arr[i].Gz - mean.Gz);
    }

    res.Ax = std::sqrt(res.Ax / size);
    res.Ay = std::sqrt(res.Ay / size);
    res.Az = std::sqrt(res.Az / size);
    res.Gx = std::sqrt(res.Gx / size);
    res.Gy = std::sqrt(res.Gy / size);
    res.Gz = std::sqrt(res.Gz / size);
}

void NormalizeData(MPU6050_Data arr[], uint8_t size, MPU6050_Data &res)
{
    MPU6050_Data mean;
    MPU6050_Data sd;
    CalculateMean(arr, size, mean);
    CalculateSD(arr, size, sd);
    res.Ax = (sd.Ax / mean.Ax);
    res.Ay = (sd.Ay / mean.Ay);
    res.Az = (sd.Ax / mean.Az);
    
    res.Gx = (sd.Gx / mean.Gx);
    res.Gy = (sd.Gy / mean.Gy);
    res.Gz = (sd.Gz / mean.Gz);
}
