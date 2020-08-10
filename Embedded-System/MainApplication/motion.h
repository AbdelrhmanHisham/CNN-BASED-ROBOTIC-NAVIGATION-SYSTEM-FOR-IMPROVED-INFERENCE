/*
 * Motion.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Abdelrhman
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "Utils"
#include "Stdtypes"

void forward(U16 x);
void backward(U16 x);

void left(void);
void right(void);

void forward_right(U16 x);

void forward_left(U16 x);

void backward_right(U16 x);
void backward_left(U16 x);


void stop();


#endif /* MOTION_H_ */
