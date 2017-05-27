
project(drweb-remoterunner-wand)

set(SOURCE_WAND
	StringList.cpp
	WorkerThread.cpp
)

# Build libace-wand
add_library(remoterunner-wand STATIC
			${SOURCE_WAND}
)
