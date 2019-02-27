#include<iostream>
#include<string>
#include<vector>

#ifndef winsor_H
#define winsor_H

enum class SortOrder { asc, desc };
enum class WinsorStyle { strict, relaxed };

void winsorizeInternal(std::vector<int>&, const float& lowWinsorSize=0, const float& highWinsorSize=0, 
                       const WinsorStyle& lowWinsorStyle=WinsorStyle::relaxed, 
                       const WinsorStyle& highWinsorStyle=WinsorStyle::relaxed);

void winsorize(std::vector<int>&, const float&);

void winsorize(std::vector<int>&, const float&, const float&);

void winsorize(std::vector<int>&, const float&, const float&, const WinsorStyle& lowWinsorStyle, const WinsorStyle& highWinsorStyle);

void printArrayToConsole(const char*, const std::vector<int>&);

#endif
