/* File: appearance.h
 * Author: YangHongbo<hongbo@yang.me>
 * Created at: Sep 18th, 2014
 *
 * Copyright (c) 2014, Yang Hongbo (hongbo@yang.me) 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _BLEAL_APPEARANCE_H_
#define _BLEAL_APPEARANCE_H_

// refer: https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.gap.appearance.xml
typedef enum bleal_appearance_t{
    BLEAL_APPEARANCE_UNKNOWN = 0,
    BLEAL_APPEARANCE_GENERIC_PHONE = 64,
    BLEAL_APPEARANCE_GENERIC_COMPUTER = 128,
    BLEAL_APPEARANCE_GENERIC_WATCH = 192,
    BLEAL_APPEARANCE_SPORTS_WATCH = 193,
    BLEAL_APPEARANCE_CLOCK = 256,
    BLEAL_APPEARANCE_DISPLAY = 320,
    BLEAL_APPEARANCE_REMOTE_CONTROL = 384,
    BLEAL_APPEARANCE_EYE_GLASSES = 448,
    BLEAL_APPEARANCE_TAG = 512,
    BLEAL_APPEARANCE_GENERIC_KEYRING = 576,
    BLEAL_APPEARANCE_GENERIC_MEDIA_PLAYER = 640,
    BLEAL_APPEARANCE_GENERIC_BARCODE_SCANNER = 704,
    BLEAL_APPEARANCE_GENERIC_THERMOMETER = 768,
    BLEAL_APPEARANCE_THERMOMETER_EAR = 769,
    BLEAL_APPEARANCE_GENERIC_HEART_RATE_SENSOR = 832,
    BLEAL_APPEARANCE_HEART_RATE_BELT = 833,
    BLEAL_APPEARANCE_GENERIC_BLOOD_PRESSURE = 896,
    BLEAL_APPEARANCE_BLOOD_PRESSURE_ARM = 897,
    BLEAL_APPEARANCE_BLOOD_PRESSURE_WRIST = 898,
    BLEAL_APPEARANCE_HUMAN_INTERFACE_DEVICE = 960,
    BLEAL_APPEARANCE_KEYBOARD = 961,
    BLEAL_APPEARANCE_MOUSE = 962,
    BLEAL_APPEARANCE_JOYSTICK = 963,
    BLEAL_APPEARANCE_GAMEPAD = 964,
    BLEAL_APPEARANCE_DIGITIZER_TABLET = 965,
    BLEAL_APPEARANCE_CARD_READER = 966,
    BLEAL_APPEARANCE_DIGITAL_PEN = 967,
    BLEAL_APPEARANCE_BARCODE_SCANNER = 968,
    BLEAL_APPEARANCE_GENERIC_GLUCOSE_METER = 1024,
    BLEAL_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR = 1088,
    BLEAL_APPEARANCE_RUNNING_WALKING_SENSOR_IN_SHOE = 1089,
    BLEAL_APPEARANCE_RUNNING_WALKING_SENSOR_ON_SHOE = 1090,
    BLEAL_APPEARANCE_RUNNING_WALKING_SENSOR_ON_HIP = 1091,
    BLEAL_APPEARANCE_CYCLING = 1152,
    BLEAL_APPEARANCE_CYCLING_COMPUTER = 1153,
    BLEAL_APPEARANCE_CYCLING_SPEED_SENSOR = 1154,
    BLEAL_APPEARANCE_CYCLING_CADENCE_SENSOR = 1155,
    BLEAL_APPEARANCE_CYCLING_POWER_SENSOR = 1156,
    BLEAL_APPEARANCE_CYCLING_SPEED_CADENCE_SENSOR = 1157,
    BLEAL_APPEARANCE_GENERIC_PULSE_OXIMETER = 3136,
    BLEAL_APPEARANCE_FINGER_TIP = 3137,
    BLEAL_APPEARANCE_WRIST_WORN = 3138,
    BLEAL_APPEARANCE_GENERIC_WEIGHT_SCALE = 3200,
    BLEAL_APPEARANCE_GENERIC_OUTDOOR_SPORTS_ACTIVITY = 5184,
    BLEAL_APPEARANCE_LOCATION_DISPLAY_DEVICE = 5185,
    BLEAL_APPEARANCE_LOCATION_NAVIGATION_DISPLAY_DEVICE = 5186,
    BLEAL_APPEARANCE_LOCATION_POD = 5187,
    BLEAL_APPEARANCE_LOCATION_NAVIGATION_POD = 5188,
} bleal_appearance_t;

#endif // _BLEAL_APPEARANCE_H_
