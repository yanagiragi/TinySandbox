all: main

CC=g++
OUT=_Executable/TinySandbox
INCLUDE_DIR=includes
SRC_DIR=src/
FLAGS=-I${INCLUDE_DIR} -lglfw -ldl --std=c++11
OBJS= \
	glad.o \
	tiny_obj_loader.o \
	TinySandbox.o \
	GraphicsAPI.o \
	Windows.o \
	Scene.o \
	BaseMaterial.o \
	BRDFLutGenerator.o \
	BRDFLutMaterial.o \
	CookTorranceMaterial.o \
	CubemapConverter.o \
	CubemapConvolveMaterial.o \
	CubemapPrefilterMaterial.o \
	DirectionalLight.o \
	EquirectangularToCubemapMaterial.o \
	GLFW_Windows.o \
	GraphicsAPI.o \
	GraphicsAPI_OpenGL.o \
	Mesh.o \
	MeshRenderer.o \
	Renderer.o \
	RotateAxis.o \
	SkyboxMaterial.o \
	SkyboxRenderer.o \
	Texture.o \

main: $(OBJS)
	$(CC) -o $(OUT) $^ $(FLAGS)

%.o: ${SRC_DIR}/%.cpp
	$(CC) -c -o $@ $< $(FLAGS)

glad.o: ${INCLUDE_DIR}/glad.c
	$(CC) -c -o $@ $< $(FLAGS)

tiny_obj_loader.o: ${INCLUDE_DIR}/TinyObjLoader/tiny_obj_loader.cc
	$(CC) -c -o $@ $< $(FLAGS)

.PHONY: clean

clean:
	rm -f $(OUT) *.o

