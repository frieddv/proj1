//
// Created by frieddv on 12/26/18.
//

#ifndef PROJ1_CONNECTTOCLIENT_H
#define PROJ1_CONNECTTOCLIENT_H

#include <pthread.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include "VariableManager.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <regex>
#include <chrono>
#include <bits/stdc++.h>


using namespace std;

void* ConnectToClient(void* args);

#endif