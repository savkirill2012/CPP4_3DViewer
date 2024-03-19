# QtGifImage CMake

---

The project was ported to the CMake build system as Shared library

---

## Install and Configuration

1. Add git submodule

```shell
mkdir third_party
cd third_party && git submodule add https://github.com/tonitaga/QtGifImage.git
```

2. The project tree must be

```tree
|   CMakeLists.txt
+---src
|   |   main.cc
|   |   
|   \---view
|           files     
\---third_party
```

3. Configure root CMakeLists.txt

```cmake

add_subdirectory(third_party/QtGifImage)

set(LINK_LIBRARIES
        QtGifImage::QtGifImage
        # other link libraries
        # For example:
        Qt${QT_VERSION_MAJOR}::Widgets
)

# ... QT generated CMakeLists.txt content
# after add_executable 

target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})

```