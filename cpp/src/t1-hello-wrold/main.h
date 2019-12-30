#pragma once

#include <iostream>

#include <stdio.h>
#include <string>
#include <vector>

#include<iostream>
#include<fstream>
#include <sstream> 

#include "../../src/shared/core/FileUtil.h"
#include "../../src/shared/platform/WindowSDL.h"
#include "../../src/shared/graphics/Graphics.h"
#include "../../src/shared/graphics/Shader.h"
#include "../../src/shared/util/Cube.h"


void handleKeys(unsigned char key, int x, int y);
void updateStep();
void initApp();