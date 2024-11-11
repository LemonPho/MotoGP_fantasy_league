cmake_minimum_required(VERSION 3.29)
project(MotoGP_Fantasy_League_Modern)

set(CMAKE_CXX_STANDARD 17)

add_executable(MotoGP_Fantasy_League 
	src/main.cpp

	include/core/Core.h
	include/core/Logger.h
	include/models/Member.h
	include/models/Rider.h
	include/models/RiderManager.h
	include/ui/DynamicUi/DynamicUi.h
	
	
	include/ui/Menu.h
	include/ui/MemberMenu.h
	include/ui/SeasonMenu.h
	include/utils/Util.h
	include/views/MemberList.h
	include/views/RiderManagerList.h

	src/core/Core.cpp
	src/core/Logger.cpp
	src/models/Member.cpp
	src/models/Rider.cpp
	src/models/RiderManager.cpp
	src/ui/DynamicUi/DynamicUi.cpp
	
	
	src/ui/Menu.cpp
	src/ui/MemberMenu.cpp
	src/ui/SeasonMenu.cpp
	src/utils/Util.cpp
	src/views/MemberList.cpp
	src/views/RiderManagerList.cpp "include/ui/DynamicUi/MultipleSelectionUi.h" "include/ui/DynamicUi/SingleSelectionUi.h" "include/ui/DynamicUi/LimitedSelectionUi.h" "src/ui/DynamicUi/MultipleSelectionUi.cpp" "src/ui/DynamicUi/LimitedSelectionUi.cpp" "src/ui/DynamicUi/SingleSelectionUi.cpp" "include/ui/DynamicUi/RidersSelectorUi.h" "src/ui/DynamicUi/RidersSelectorUi.cpp" "include/models/Season.h" "src/models/Season.cpp" "include/ui/DynamicUi/DynamicUiElement/BaseUiElement.h" "src/ui/DynamicUi/DynamicUiElement/BaseUiElement.cpp")

target_include_directories(MotoGP_Fantasy_League PRIVATE ${CMAKE_SOURCE_DIR}/include)
