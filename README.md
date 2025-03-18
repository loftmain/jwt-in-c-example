# s2o Project

This project is a simple C application that demonstrates how to encode JSON Web Tokens (JWT) using the `l8w8jwt` library. The application generates a JWT with specified claims and outputs it to the console.

https://github.com/GlitchedPolygons/l8w8jwt

git submodule add https://github.com/GlitchedPolygons/l8w8jwt.git src/lib/l8w8jwt
git submodule update --init --recursive

## Project Structure

```
s2o
├── CMakeLists.txt
├── src
│   ├── l8w8.c
│   └── l8w8jwt
│       └── encode.h
└── README.md
```

## Files Description

- **CMakeLists.txt**: This file contains the build configuration for CMake, defining the project's build settings, source files, header files, and build options.

- **src/l8w8.c**: This is the main C program that includes functionality for encoding JWTs. It utilizes the `l8w8jwt` library to create and output the JWT.

- **src/l8w8jwt/encode.h**: This header file contains declarations for functions and structures necessary for JWT encoding. It defines the parameter structure and related functions for JWT encoding.

## How to Use CMake

1. Open a terminal and navigate to the project directory.
2. Create a build directory with the command:
   ```
   mkdir build
   ```
3. Change into the build directory:
   ```
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project using:
   ```
   make
   ```
6. Once the build is complete, you can run the executable with:
   ```
   ./s2o
   ```

## Example Output

When you run the application, it will generate and display a JWT token based on the specified claims and secret key.