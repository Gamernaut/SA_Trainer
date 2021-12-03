#include "pch.h"
#include "..\src\MathsFunctions.h"

#include "gtest/gtest.h"

// code from https://github.com/google/googletest/blob/main/docs/primer.md

using namespace cpv;

// Pythagoras calculator    https://www.google.com/search?q=pythagoras+calculator

TEST(MathsFunction, Distance1) {
    Coordinate point_a = {0 , 0};
    Coordinate point_b = {0 , 0};
    EXPECT_EQ(distance_between_point_a_and_b_in_pixels(point_a, point_b), 0);
}

TEST(MathsFunction, Distance2) {
    Coordinate point_a = { 0 , 0 };
    Coordinate point_b = { 100 , 0 };
    EXPECT_EQ(distance_between_point_a_and_b_in_pixels(point_a, point_b), 100);
}

TEST(MathsFunction, Distance3) {
    Coordinate point_a = { 0 , 0 };
    Coordinate point_b = { 100 , 100 };
    EXPECT_EQ(distance_between_point_a_and_b_in_pixels(point_a, point_b), 141);
}

TEST(MathsFunction, Angle1) {
    Coordinate point_a = { 0 , 0 };
    Coordinate point_b = { 100 , 0 };
    EXPECT_EQ(angle_between_point_a_and_b(point_a, point_b), 90);
}

TEST(MathsFunction, Angle2) {
    Coordinate point_a = { 0 , 0 };
    Coordinate point_b = { 0 , 100 };
    EXPECT_EQ(angle_between_point_a_and_b(point_a, point_b), 180);
}

TEST(MathsFunction, Angle3) {
    Coordinate point_a = { 100 , 100 };
    Coordinate point_b = { 50 ,  100 };
    EXPECT_EQ(angle_between_point_a_and_b(point_a, point_b), 270);
}

TEST(MathsFunction, EndPoint1) {
    Coordinate point_a = { 100 , 100 };
    int bogey_current_heading = 90;
    int my_aircraft_current_heading = 0;
    int line_length = 20;
    EXPECT_EQ(endpoint_given_start_and_bearing(point_a, bogey_current_heading, my_aircraft_current_heading, line_length), 120);
}

TEST(MathsFunction, EndPoint2) {
    Coordinate point_a = { 100 , 100 };
    int bogey_current_heading = 180;
    int my_aircraft_current_heading = 0;
    int line_length = 20;
    EXPECT_EQ(endpoint_given_start_and_bearing(point_a, bogey_current_heading, my_aircraft_current_heading, line_length), 100);
}

TEST(MathsFunction, EndPoint3) {
    Coordinate point_a = { 100 , 100 };
    int bogey_current_heading = 90;
    int my_aircraft_current_heading = 90;
    int line_length = 20;
    EXPECT_EQ(endpoint_given_start_and_bearing(point_a, bogey_current_heading, my_aircraft_current_heading, line_length), 100);
}