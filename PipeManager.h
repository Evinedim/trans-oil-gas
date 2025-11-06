#pragma once
#include <iostream>
#include <unordered_map>
#include "Pipe.h"

void filterPipesByName(std::unordered_map<int, Pipe>& pipes);

void filterPipesByStatus(std::unordered_map<int, Pipe>& pipes);

void changeStatusById(int id, std::unordered_map<int, Pipe>& pipes);

void deletePipeById(int id, std::unordered_map<int, Pipe>& pipes);

void pipeManager(int id, std::unordered_map<int, Pipe>& pipes);
