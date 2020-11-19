#pragma once
/*
*Author:Pozzitron1337
*gitHub:Pozzitron1337
*/

#include "common.cpp"
#include "roPollard.cpp"
#include "ferma.cpp"
#include "brilhartMorrison.cpp"
#include "lenstra.cpp"
#include "silver_polig_hellman.cpp"
#define unsigned long long

#ifndef NUMBERALGORITHMS_H_
#define NUMBERALGORITHMS_H_

long gcd (long a, long b);
long gcd_not_verbose(long a,long b);
long get_hight_bit(long x);
long f_1(long x,long n);
long f_2(long x,long n);
long f_3(long x,long n);
long f_4(long x,long n);
long roPolard_2_in_power_h_(long (*F)(long,long),long n, long x_0);
long roPolard_j_equals_2k(long (*F)(long,long),long n, long x_0);
long roPolard_classic(long (*F)(long,long),long n, long x_0);
map<long,long> factorize(long n);
long brilhart_morrison(long n);
void task_3_lenstra(long n);
long silver_polig_hellman(long a,long b,long p);

#endif

