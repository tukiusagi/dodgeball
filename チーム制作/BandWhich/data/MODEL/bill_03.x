xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 396;
 -34.10000;163.57183;-49.32000;,
 -20.46000;163.57183;-49.32000;,
 -20.46000;130.76782;-49.32000;,
 -34.10000;130.76782;-49.32000;,
 -6.82000;163.57183;-49.32000;,
 -6.82000;130.76782;-49.32000;,
 6.82000;163.57183;-49.32000;,
 6.82000;130.76782;-49.32000;,
 20.46000;163.57183;-49.32000;,
 20.46000;130.76782;-49.32000;,
 34.10000;163.57183;-49.32000;,
 34.10000;130.76782;-49.32000;,
 -20.46000;97.96382;-49.32000;,
 -34.10000;97.96382;-49.32000;,
 -6.82000;97.96382;-49.32000;,
 6.82000;97.96382;-49.32000;,
 20.46000;97.96382;-49.32000;,
 34.10000;97.96382;-49.32000;,
 -20.46000;65.15983;-49.32000;,
 -34.10000;65.15983;-49.32000;,
 -6.82000;65.15983;-49.32000;,
 6.82000;65.15983;-49.32000;,
 20.46000;65.15983;-49.32000;,
 34.10000;65.15983;-49.32000;,
 -20.46000;32.35583;-49.32000;,
 -34.10000;32.35583;-49.32000;,
 -6.82000;32.35583;-49.32000;,
 6.82000;32.35583;-49.32000;,
 20.46000;32.35583;-49.32000;,
 34.10000;32.35583;-49.32000;,
 -20.46000;-0.44818;-49.32000;,
 -34.10000;-0.44818;-49.32000;,
 -6.82000;-0.44818;-49.32000;,
 6.82000;-0.44818;-49.32000;,
 20.46000;-0.44818;-49.32000;,
 34.10000;-0.44818;-49.32000;,
 34.10000;163.57183;-49.32000;,
 34.10000;163.57183;-32.88000;,
 34.10000;130.76782;-32.88000;,
 34.10000;130.76782;-49.32000;,
 34.10000;163.57183;-16.44000;,
 34.10000;130.76782;-16.44000;,
 34.10000;163.57183;0.00000;,
 34.10000;130.76782;0.00000;,
 34.10000;163.57183;16.44000;,
 34.10000;130.76782;16.44000;,
 34.10000;163.57183;32.88000;,
 34.10000;130.76782;32.88000;,
 34.10000;163.57183;49.32000;,
 34.10000;130.76782;49.32000;,
 34.10000;97.96382;-32.88000;,
 34.10000;97.96382;-49.32000;,
 34.10000;97.96382;-16.44000;,
 34.10000;97.96382;0.00000;,
 34.10000;97.96382;16.44000;,
 34.10000;97.96382;32.88000;,
 34.10000;97.96382;49.32000;,
 34.10000;65.15983;-32.88000;,
 34.10000;65.15983;-49.32000;,
 34.10000;65.15983;-16.44000;,
 34.10000;65.15983;0.00000;,
 34.10000;65.15983;16.44000;,
 34.10000;65.15983;32.88000;,
 34.10000;65.15983;49.32000;,
 34.10000;32.35583;-32.88000;,
 34.10000;32.35583;-49.32000;,
 34.10000;32.35583;-16.44000;,
 34.10000;32.35583;0.00000;,
 34.10000;32.35583;16.44000;,
 34.10000;32.35583;32.88000;,
 34.10000;32.35583;49.32000;,
 34.10000;-0.44818;-32.88000;,
 34.10000;-0.44818;-49.32000;,
 34.10000;-0.44818;-16.44000;,
 34.10000;-0.44818;-0.00000;,
 34.10000;-0.44818;16.44000;,
 34.10000;-0.44818;32.88000;,
 34.10000;-0.44818;49.32000;,
 34.10000;163.57183;49.32000;,
 20.46000;163.57183;49.32000;,
 20.46000;130.76782;49.32000;,
 34.10000;130.76782;49.32000;,
 6.82000;163.57183;49.32000;,
 6.82000;130.76782;49.32000;,
 -6.82000;163.57183;49.32000;,
 -6.82000;130.76782;49.32000;,
 -20.46000;163.57183;49.32000;,
 -20.46000;130.76782;49.32000;,
 -34.10000;163.57183;49.32000;,
 -34.10000;130.76782;49.32000;,
 20.46000;97.96382;49.32000;,
 34.10000;97.96382;49.32000;,
 6.82000;97.96382;49.32000;,
 -6.82000;97.96382;49.32000;,
 -20.46000;97.96382;49.32000;,
 -34.10000;97.96382;49.32000;,
 20.46000;65.15983;49.32000;,
 34.10000;65.15983;49.32000;,
 6.82000;65.15983;49.32000;,
 -6.82000;65.15983;49.32000;,
 -20.46000;65.15983;49.32000;,
 -34.10000;65.15983;49.32000;,
 20.46000;32.35583;49.32000;,
 34.10000;32.35583;49.32000;,
 6.82000;32.35583;49.32000;,
 -6.82000;32.35583;49.32000;,
 -20.46000;32.35583;49.32000;,
 -34.10000;32.35583;49.32000;,
 20.46000;-0.44818;49.32000;,
 34.10000;-0.44818;49.32000;,
 6.82000;-0.44818;49.32000;,
 -6.82000;-0.44818;49.32000;,
 -20.46000;-0.44818;49.32000;,
 -34.10000;-0.44818;49.32000;,
 -34.10000;163.57183;49.32000;,
 -34.10000;163.57183;32.88000;,
 -34.10000;130.76782;32.88000;,
 -34.10000;130.76782;49.32000;,
 -34.10000;163.57183;16.44000;,
 -34.10000;130.76782;16.44000;,
 -34.10000;163.57183;0.00000;,
 -34.10000;130.76782;0.00000;,
 -34.10000;163.57183;-16.44000;,
 -34.10000;130.76782;-16.44000;,
 -34.10000;163.57183;-32.88000;,
 -34.10000;130.76782;-32.88000;,
 -34.10000;163.57183;-49.32000;,
 -34.10000;130.76782;-49.32000;,
 -34.10000;97.96382;32.88000;,
 -34.10000;97.96382;49.32000;,
 -34.10000;97.96382;16.44000;,
 -34.10000;97.96382;0.00000;,
 -34.10000;97.96382;-16.44000;,
 -34.10000;97.96382;-32.88000;,
 -34.10000;97.96382;-49.32000;,
 -34.10000;65.15983;32.88000;,
 -34.10000;65.15983;49.32000;,
 -34.10000;65.15983;16.44000;,
 -34.10000;65.15983;0.00000;,
 -34.10000;65.15983;-16.44000;,
 -34.10000;65.15983;-32.88000;,
 -34.10000;65.15983;-49.32000;,
 -34.10000;32.35583;32.88000;,
 -34.10000;32.35583;49.32000;,
 -34.10000;32.35583;16.44000;,
 -34.10000;32.35583;0.00000;,
 -34.10000;32.35583;-16.44000;,
 -34.10000;32.35583;-32.88000;,
 -34.10000;32.35583;-49.32000;,
 -34.10000;-0.44818;32.88000;,
 -34.10000;-0.44818;49.32000;,
 -34.10000;-0.44818;16.44000;,
 -34.10000;-0.44818;0.00000;,
 -34.10000;-0.44818;-16.44000;,
 -34.10000;-0.44818;-32.88000;,
 -34.10000;-0.44818;-49.32000;,
 -20.46000;163.57183;49.32000;,
 -20.46000;163.57183;32.88000;,
 -34.10000;163.57183;32.88000;,
 -6.82000;163.57183;49.32000;,
 -6.82000;163.57183;32.88000;,
 6.82000;163.57183;49.32000;,
 6.82000;163.57183;32.88000;,
 20.46000;163.57183;49.32000;,
 20.46000;163.57183;32.88000;,
 34.10000;163.57183;32.88000;,
 -20.46000;163.57183;16.44000;,
 -34.10000;163.57183;16.44000;,
 -6.82000;163.57183;16.44000;,
 6.82000;163.57183;16.44000;,
 20.46000;163.57183;16.44000;,
 34.10000;163.57183;16.44000;,
 -20.46000;163.57183;0.00000;,
 -34.10000;163.57183;0.00000;,
 -6.82000;163.57183;0.00000;,
 6.82000;163.57183;0.00000;,
 20.46000;163.57183;0.00000;,
 34.10000;163.57183;0.00000;,
 -20.46000;163.57183;-16.44000;,
 -34.10000;163.57183;-16.44000;,
 -6.82000;163.57183;-16.44000;,
 6.82000;163.57183;-16.44000;,
 20.46000;163.57183;-16.44000;,
 34.10000;163.57183;-16.44000;,
 -20.46000;163.57183;-32.88000;,
 -34.10000;163.57183;-32.88000;,
 -6.82000;163.57183;-32.88000;,
 6.82000;163.57183;-32.88000;,
 20.46000;163.57183;-32.88000;,
 34.10000;163.57183;-32.88000;,
 -20.46000;163.57183;-49.32000;,
 -34.10000;163.57183;-49.32000;,
 -6.82000;163.57183;-49.32000;,
 6.82000;163.57183;-49.32000;,
 20.46000;163.57183;-49.32000;,
 34.10000;163.57183;-49.32000;,
 -34.10000;163.57183;-148.15059;,
 -20.46000;163.57183;-148.15059;,
 -20.46000;130.76782;-148.15059;,
 -34.10000;130.76782;-148.15059;,
 -6.82000;163.57183;-148.15059;,
 -6.82000;130.76782;-148.15059;,
 6.82000;163.57183;-148.15059;,
 6.82000;130.76782;-148.15059;,
 20.46000;163.57183;-148.15059;,
 20.46000;130.76782;-148.15059;,
 34.10000;163.57183;-148.15059;,
 34.10000;130.76782;-148.15059;,
 -20.46000;97.96382;-148.15059;,
 -34.10000;97.96382;-148.15059;,
 -6.82000;97.96382;-148.15059;,
 6.82000;97.96382;-148.15059;,
 20.46000;97.96382;-148.15059;,
 34.10000;97.96382;-148.15059;,
 -20.46000;65.15983;-148.15059;,
 -34.10000;65.15983;-148.15059;,
 -6.82000;65.15983;-148.15059;,
 6.82000;65.15983;-148.15059;,
 20.46000;65.15983;-148.15059;,
 34.10000;65.15983;-148.15059;,
 -20.46000;32.35583;-148.15059;,
 -34.10000;32.35583;-148.15059;,
 -6.82000;32.35583;-148.15059;,
 6.82000;32.35583;-148.15059;,
 20.46000;32.35583;-148.15059;,
 34.10000;32.35583;-148.15059;,
 -20.46000;-0.44818;-148.15059;,
 -34.10000;-0.44818;-148.15059;,
 -6.82000;-0.44818;-148.15059;,
 6.82000;-0.44818;-148.15059;,
 20.46000;-0.44818;-148.15059;,
 34.10000;-0.44818;-148.15059;,
 34.10000;163.57183;-148.15059;,
 34.10000;163.57183;-131.71059;,
 34.10000;130.76782;-131.71059;,
 34.10000;130.76782;-148.15059;,
 34.10000;163.57183;-115.27058;,
 34.10000;130.76782;-115.27058;,
 34.10000;163.57183;-98.83059;,
 34.10000;130.76782;-98.83059;,
 34.10000;163.57183;-82.39059;,
 34.10000;130.76782;-82.39059;,
 34.10000;163.57183;-65.95059;,
 34.10000;130.76782;-65.95059;,
 34.10000;163.57183;-49.51059;,
 34.10000;130.76782;-49.51059;,
 34.10000;97.96382;-131.71059;,
 34.10000;97.96382;-148.15059;,
 34.10000;97.96382;-115.27058;,
 34.10000;97.96382;-98.83059;,
 34.10000;97.96382;-82.39059;,
 34.10000;97.96382;-65.95059;,
 34.10000;97.96382;-49.51059;,
 34.10000;65.15983;-131.71059;,
 34.10000;65.15983;-148.15059;,
 34.10000;65.15983;-115.27058;,
 34.10000;65.15983;-98.83059;,
 34.10000;65.15983;-82.39059;,
 34.10000;65.15983;-65.95059;,
 34.10000;65.15983;-49.51059;,
 34.10000;32.35583;-131.71059;,
 34.10000;32.35583;-148.15059;,
 34.10000;32.35583;-115.27058;,
 34.10000;32.35583;-98.83059;,
 34.10000;32.35583;-82.39059;,
 34.10000;32.35583;-65.95059;,
 34.10000;32.35583;-49.51059;,
 34.10000;-0.44818;-131.71059;,
 34.10000;-0.44818;-148.15059;,
 34.10000;-0.44818;-115.27058;,
 34.10000;-0.44818;-98.83059;,
 34.10000;-0.44818;-82.39059;,
 34.10000;-0.44818;-65.95059;,
 34.10000;-0.44818;-49.51059;,
 34.10000;163.57183;-49.51059;,
 20.46000;163.57183;-49.51059;,
 20.46000;130.76782;-49.51059;,
 34.10000;130.76782;-49.51059;,
 6.82000;163.57183;-49.51059;,
 6.82000;130.76782;-49.51059;,
 -6.82000;163.57183;-49.51059;,
 -6.82000;130.76782;-49.51059;,
 -20.46000;163.57183;-49.51059;,
 -20.46000;130.76782;-49.51059;,
 -34.10000;163.57183;-49.51059;,
 -34.10000;130.76782;-49.51059;,
 20.46000;97.96382;-49.51059;,
 34.10000;97.96382;-49.51059;,
 6.82000;97.96382;-49.51059;,
 -6.82000;97.96382;-49.51059;,
 -20.46000;97.96382;-49.51059;,
 -34.10000;97.96382;-49.51059;,
 20.46000;65.15983;-49.51059;,
 34.10000;65.15983;-49.51059;,
 6.82000;65.15983;-49.51059;,
 -6.82000;65.15983;-49.51059;,
 -20.46000;65.15983;-49.51059;,
 -34.10000;65.15983;-49.51059;,
 20.46000;32.35583;-49.51059;,
 34.10000;32.35583;-49.51059;,
 6.82000;32.35583;-49.51059;,
 -6.82000;32.35583;-49.51059;,
 -20.46000;32.35583;-49.51059;,
 -34.10000;32.35583;-49.51059;,
 20.46000;-0.44818;-49.51059;,
 34.10000;-0.44818;-49.51059;,
 6.82000;-0.44818;-49.51059;,
 -6.82000;-0.44818;-49.51059;,
 -20.46000;-0.44818;-49.51059;,
 -34.10000;-0.44818;-49.51059;,
 -34.10000;163.57183;-49.51059;,
 -34.10000;163.57183;-65.95059;,
 -34.10000;130.76782;-65.95059;,
 -34.10000;130.76782;-49.51059;,
 -34.10000;163.57183;-82.39059;,
 -34.10000;130.76782;-82.39059;,
 -34.10000;163.57183;-98.83059;,
 -34.10000;130.76782;-98.83059;,
 -34.10000;163.57183;-115.27058;,
 -34.10000;130.76782;-115.27058;,
 -34.10000;163.57183;-131.71059;,
 -34.10000;130.76782;-131.71059;,
 -34.10000;163.57183;-148.15059;,
 -34.10000;130.76782;-148.15059;,
 -34.10000;97.96382;-65.95059;,
 -34.10000;97.96382;-49.51059;,
 -34.10000;97.96382;-82.39059;,
 -34.10000;97.96382;-98.83059;,
 -34.10000;97.96382;-115.27058;,
 -34.10000;97.96382;-131.71059;,
 -34.10000;97.96382;-148.15059;,
 -34.10000;65.15983;-65.95059;,
 -34.10000;65.15983;-49.51059;,
 -34.10000;65.15983;-82.39059;,
 -34.10000;65.15983;-98.83059;,
 -34.10000;65.15983;-115.27058;,
 -34.10000;65.15983;-131.71059;,
 -34.10000;65.15983;-148.15059;,
 -34.10000;32.35583;-65.95059;,
 -34.10000;32.35583;-49.51059;,
 -34.10000;32.35583;-82.39059;,
 -34.10000;32.35583;-98.83059;,
 -34.10000;32.35583;-115.27058;,
 -34.10000;32.35583;-131.71059;,
 -34.10000;32.35583;-148.15059;,
 -34.10000;-0.44818;-65.95059;,
 -34.10000;-0.44818;-49.51059;,
 -34.10000;-0.44818;-82.39059;,
 -34.10000;-0.44818;-98.83059;,
 -34.10000;-0.44818;-115.27058;,
 -34.10000;-0.44818;-131.71059;,
 -34.10000;-0.44818;-148.15059;,
 -20.46000;163.57183;-49.51059;,
 -20.46000;163.57183;-65.95059;,
 -34.10000;163.57183;-65.95059;,
 -6.82000;163.57183;-49.51059;,
 -6.82000;163.57183;-65.95059;,
 6.82000;163.57183;-49.51059;,
 6.82000;163.57183;-65.95059;,
 20.46000;163.57183;-49.51059;,
 20.46000;163.57183;-65.95059;,
 34.10000;163.57183;-65.95059;,
 -20.46000;163.57183;-82.39059;,
 -34.10000;163.57183;-82.39059;,
 -6.82000;163.57183;-82.39059;,
 6.82000;163.57183;-82.39059;,
 20.46000;163.57183;-82.39059;,
 34.10000;163.57183;-82.39059;,
 -20.46000;163.57183;-98.83059;,
 -34.10000;163.57183;-98.83059;,
 -6.82000;163.57183;-98.83059;,
 6.82000;163.57183;-98.83059;,
 20.46000;163.57183;-98.83059;,
 34.10000;163.57183;-98.83059;,
 -20.46000;163.57183;-115.27058;,
 -34.10000;163.57183;-115.27058;,
 -6.82000;163.57183;-115.27058;,
 6.82000;163.57183;-115.27058;,
 20.46000;163.57183;-115.27058;,
 34.10000;163.57183;-115.27058;,
 -20.46000;163.57183;-131.71059;,
 -34.10000;163.57183;-131.71059;,
 -6.82000;163.57183;-131.71059;,
 6.82000;163.57183;-131.71059;,
 20.46000;163.57183;-131.71059;,
 34.10000;163.57183;-131.71059;,
 -20.46000;163.57183;-148.15059;,
 -34.10000;163.57183;-148.15059;,
 -6.82000;163.57183;-148.15059;,
 6.82000;163.57183;-148.15059;,
 20.46000;163.57183;-148.15059;,
 34.10000;163.57183;-148.15059;,
 -34.17226;23.79529;-33.40518;,
 -34.17190;23.58246;-65.87355;,
 -34.15461;-0.83944;-65.59086;,
 -34.15498;-0.62661;-33.12250;;
 
 281;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;3,2,12,13;,
 4;2,5,14,12;,
 4;5,7,15,14;,
 4;7,9,16,15;,
 4;9,11,17,16;,
 4;13,12,18,19;,
 4;12,14,20,18;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 4;16,17,23,22;,
 4;19,18,24,25;,
 4;18,20,26,24;,
 4;20,21,27,26;,
 4;21,22,28,27;,
 4;22,23,29,28;,
 4;25,24,30,31;,
 4;24,26,32,30;,
 4;26,27,33,32;,
 4;27,28,34,33;,
 4;28,29,35,34;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;39,38,50,51;,
 4;38,41,52,50;,
 4;41,43,53,52;,
 4;43,45,54,53;,
 4;45,47,55,54;,
 4;47,49,56,55;,
 4;51,50,57,58;,
 4;50,52,59,57;,
 4;52,53,60,59;,
 4;53,54,61,60;,
 4;54,55,62,61;,
 4;55,56,63,62;,
 4;58,57,64,65;,
 4;57,59,66,64;,
 4;59,60,67,66;,
 4;60,61,68,67;,
 4;61,62,69,68;,
 4;62,63,70,69;,
 4;65,64,71,72;,
 4;64,66,73,71;,
 4;66,67,74,73;,
 4;67,68,75,74;,
 4;68,69,76,75;,
 4;69,70,77,76;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;81,80,90,91;,
 4;80,83,92,90;,
 4;83,85,93,92;,
 4;85,87,94,93;,
 4;87,89,95,94;,
 4;91,90,96,97;,
 4;90,92,98,96;,
 4;92,93,99,98;,
 4;93,94,100,99;,
 4;94,95,101,100;,
 4;97,96,102,103;,
 4;96,98,104,102;,
 4;98,99,105,104;,
 4;99,100,106,105;,
 4;100,101,107,106;,
 4;103,102,108,109;,
 4;102,104,110,108;,
 4;104,105,111,110;,
 4;105,106,112,111;,
 4;106,107,113,112;,
 4;114,115,116,117;,
 4;115,118,119,116;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;117,116,128,129;,
 4;116,119,130,128;,
 4;119,121,131,130;,
 4;121,123,132,131;,
 4;123,125,133,132;,
 4;125,127,134,133;,
 4;129,128,135,136;,
 4;128,130,137,135;,
 4;130,131,138,137;,
 4;131,132,139,138;,
 4;132,133,140,139;,
 4;133,134,141,140;,
 4;136,135,142,143;,
 4;135,137,144,142;,
 4;137,138,145,144;,
 4;138,139,146,145;,
 4;139,140,147,146;,
 4;140,141,148,147;,
 4;143,142,149,150;,
 4;142,144,151,149;,
 4;144,145,152,151;,
 4;145,146,153,152;,
 4;146,147,154,153;,
 4;147,148,155,154;,
 4;114,156,157,158;,
 4;156,159,160,157;,
 4;159,161,162,160;,
 4;161,163,164,162;,
 4;163,48,165,164;,
 4;158,157,166,167;,
 4;157,160,168,166;,
 4;160,162,169,168;,
 4;162,164,170,169;,
 4;164,165,171,170;,
 4;167,166,172,173;,
 4;166,168,174,172;,
 4;168,169,175,174;,
 4;169,170,176,175;,
 4;170,171,177,176;,
 4;173,172,178,179;,
 4;172,174,180,178;,
 4;174,175,181,180;,
 4;175,176,182,181;,
 4;176,177,183,182;,
 4;179,178,184,185;,
 4;178,180,186,184;,
 4;180,181,187,186;,
 4;181,182,188,187;,
 4;182,183,189,188;,
 4;185,184,190,191;,
 4;184,186,192,190;,
 4;186,187,193,192;,
 4;187,188,194,193;,
 4;188,189,195,194;,
 4;196,197,198,199;,
 4;197,200,201,198;,
 4;200,202,203,201;,
 4;202,204,205,203;,
 4;204,206,207,205;,
 4;199,198,208,209;,
 4;198,201,210,208;,
 4;201,203,211,210;,
 4;203,205,212,211;,
 4;205,207,213,212;,
 4;209,208,214,215;,
 4;208,210,216,214;,
 4;210,211,217,216;,
 4;211,212,218,217;,
 4;212,213,219,218;,
 4;215,214,220,221;,
 4;214,216,222,220;,
 4;216,217,223,222;,
 4;217,218,224,223;,
 4;218,219,225,224;,
 4;221,220,226,227;,
 4;220,222,228,226;,
 4;222,223,229,228;,
 4;223,224,230,229;,
 4;224,225,231,230;,
 4;232,233,234,235;,
 4;233,236,237,234;,
 4;236,238,239,237;,
 4;238,240,241,239;,
 4;240,242,243,241;,
 4;242,244,245,243;,
 4;235,234,246,247;,
 4;234,237,248,246;,
 4;237,239,249,248;,
 4;239,241,250,249;,
 4;241,243,251,250;,
 4;243,245,252,251;,
 4;247,246,253,254;,
 4;246,248,255,253;,
 4;248,249,256,255;,
 4;249,250,257,256;,
 4;250,251,258,257;,
 4;251,252,259,258;,
 4;254,253,260,261;,
 4;253,255,262,260;,
 4;255,256,263,262;,
 4;256,257,264,263;,
 4;257,258,265,264;,
 4;258,259,266,265;,
 4;261,260,267,268;,
 4;260,262,269,267;,
 4;262,263,270,269;,
 4;263,264,271,270;,
 4;264,265,272,271;,
 4;265,266,273,272;,
 4;274,275,276,277;,
 4;275,278,279,276;,
 4;278,280,281,279;,
 4;280,282,283,281;,
 4;282,284,285,283;,
 4;277,276,286,287;,
 4;276,279,288,286;,
 4;279,281,289,288;,
 4;281,283,290,289;,
 4;283,285,291,290;,
 4;287,286,292,293;,
 4;286,288,294,292;,
 4;288,289,295,294;,
 4;289,290,296,295;,
 4;290,291,297,296;,
 4;293,292,298,299;,
 4;292,294,300,298;,
 4;294,295,301,300;,
 4;295,296,302,301;,
 4;296,297,303,302;,
 4;299,298,304,305;,
 4;298,300,306,304;,
 4;300,301,307,306;,
 4;301,302,308,307;,
 4;302,303,309,308;,
 4;310,311,312,313;,
 4;311,314,315,312;,
 4;314,316,317,315;,
 4;316,318,319,317;,
 4;318,320,321,319;,
 4;320,322,323,321;,
 4;313,312,324,325;,
 4;312,315,326,324;,
 4;315,317,327,326;,
 4;317,319,328,327;,
 4;319,321,329,328;,
 4;321,323,330,329;,
 4;325,324,331,332;,
 4;324,326,333,331;,
 4;326,327,334,333;,
 4;327,328,335,334;,
 4;328,329,336,335;,
 4;329,330,337,336;,
 4;332,331,338,339;,
 4;331,333,340,338;,
 4;333,334,341,340;,
 4;334,335,342,341;,
 4;335,336,343,342;,
 4;336,337,344,343;,
 4;339,338,345,346;,
 4;338,340,347,345;,
 4;340,341,348,347;,
 4;341,342,349,348;,
 4;342,343,350,349;,
 4;343,344,351,350;,
 4;310,352,353,354;,
 4;352,355,356,353;,
 4;355,357,358,356;,
 4;357,359,360,358;,
 4;359,244,361,360;,
 4;354,353,362,363;,
 4;353,356,364,362;,
 4;356,358,365,364;,
 4;358,360,366,365;,
 4;360,361,367,366;,
 4;363,362,368,369;,
 4;362,364,370,368;,
 4;364,365,371,370;,
 4;365,366,372,371;,
 4;366,367,373,372;,
 4;369,368,374,375;,
 4;368,370,376,374;,
 4;370,371,377,376;,
 4;371,372,378,377;,
 4;372,373,379,378;,
 4;375,374,380,381;,
 4;374,376,382,380;,
 4;376,377,383,382;,
 4;377,378,384,383;,
 4;378,379,385,384;,
 4;381,380,386,387;,
 4;380,382,388,386;,
 4;382,383,389,388;,
 4;383,384,390,389;,
 4;384,385,391,390;,
 4;392,393,394,395;;
 
 MeshMaterialList {
  3;
  281;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\マンション カベ.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\自動ドア.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game341\\Pictures\\GM01_37tsuchida_daiki\\lesson10_Building\\tex\\wall&te\\SH048_L.jpg";
   }
  }
 }
 MeshNormals {
  11;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;-0.000708;-0.000007;;
  281;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;10,10,10,10;;
 }
 MeshTextureCoords {
  396;
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.400000;0.400000;,
  0.600000;0.400000;,
  0.800000;0.400000;,
  1.000000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.400000;0.800000;,
  0.600000;0.800000;,
  0.800000;0.800000;,
  1.000000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.200000;,
  0.000000;0.200000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.500000;0.000000;,
  0.500000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  0.833330;0.000000;,
  0.833330;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.166670;0.400000;,
  0.000000;0.400000;,
  0.333330;0.400000;,
  0.500000;0.400000;,
  0.666670;0.400000;,
  0.833330;0.400000;,
  1.000000;0.400000;,
  0.166670;0.600000;,
  0.000000;0.600000;,
  0.333330;0.600000;,
  0.500000;0.600000;,
  0.666670;0.600000;,
  0.833330;0.600000;,
  1.000000;0.600000;,
  0.166670;0.800000;,
  0.000000;0.800000;,
  0.333330;0.800000;,
  0.500000;0.800000;,
  0.666670;0.800000;,
  0.833330;0.800000;,
  1.000000;0.800000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.400000;0.400000;,
  0.600000;0.400000;,
  0.800000;0.400000;,
  1.000000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.400000;0.800000;,
  0.600000;0.800000;,
  0.800000;0.800000;,
  1.000000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.200000;,
  0.000000;0.200000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.500000;0.000000;,
  0.500000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  0.833330;0.000000;,
  0.833330;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.166670;0.400000;,
  0.000000;0.400000;,
  0.333330;0.400000;,
  0.500000;0.400000;,
  0.666670;0.400000;,
  0.833330;0.400000;,
  1.000000;0.400000;,
  0.166670;0.600000;,
  0.000000;0.600000;,
  0.333330;0.600000;,
  0.500000;0.600000;,
  0.666670;0.600000;,
  0.833330;0.600000;,
  1.000000;0.600000;,
  0.166670;0.800000;,
  0.000000;0.800000;,
  0.333330;0.800000;,
  0.500000;0.800000;,
  0.666670;0.800000;,
  0.833330;0.800000;,
  1.000000;0.800000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.200000;0.000000;,
  0.200000;0.166670;,
  0.000000;0.166670;,
  0.400000;0.000000;,
  0.400000;0.166670;,
  0.600000;0.000000;,
  0.600000;0.166670;,
  0.800000;0.000000;,
  0.800000;0.166670;,
  1.000000;0.166670;,
  0.200000;0.333330;,
  0.000000;0.333330;,
  0.400000;0.333330;,
  0.600000;0.333330;,
  0.800000;0.333330;,
  1.000000;0.333330;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.666670;,
  0.000000;0.666670;,
  0.400000;0.666670;,
  0.600000;0.666670;,
  0.800000;0.666670;,
  1.000000;0.666670;,
  0.200000;0.833330;,
  0.000000;0.833330;,
  0.400000;0.833330;,
  0.600000;0.833330;,
  0.800000;0.833330;,
  1.000000;0.833330;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.400000;0.400000;,
  0.600000;0.400000;,
  0.800000;0.400000;,
  1.000000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.400000;0.800000;,
  0.600000;0.800000;,
  0.800000;0.800000;,
  1.000000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.200000;,
  0.000000;0.200000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.500000;0.000000;,
  0.500000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  0.833330;0.000000;,
  0.833330;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.166670;0.400000;,
  0.000000;0.400000;,
  0.333330;0.400000;,
  0.500000;0.400000;,
  0.666670;0.400000;,
  0.833330;0.400000;,
  1.000000;0.400000;,
  0.166670;0.600000;,
  0.000000;0.600000;,
  0.333330;0.600000;,
  0.500000;0.600000;,
  0.666670;0.600000;,
  0.833330;0.600000;,
  1.000000;0.600000;,
  0.166670;0.800000;,
  0.000000;0.800000;,
  0.333330;0.800000;,
  0.500000;0.800000;,
  0.666670;0.800000;,
  0.833330;0.800000;,
  1.000000;0.800000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.400000;0.400000;,
  0.600000;0.400000;,
  0.800000;0.400000;,
  1.000000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.400000;0.800000;,
  0.600000;0.800000;,
  0.800000;0.800000;,
  1.000000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.200000;,
  0.000000;0.200000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.500000;0.000000;,
  0.500000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  0.833330;0.000000;,
  0.833330;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.166670;0.400000;,
  0.000000;0.400000;,
  0.333330;0.400000;,
  0.500000;0.400000;,
  0.666670;0.400000;,
  0.833330;0.400000;,
  1.000000;0.400000;,
  0.166670;0.600000;,
  0.000000;0.600000;,
  0.333330;0.600000;,
  0.500000;0.600000;,
  0.666670;0.600000;,
  0.833330;0.600000;,
  1.000000;0.600000;,
  0.166670;0.800000;,
  0.000000;0.800000;,
  0.333330;0.800000;,
  0.500000;0.800000;,
  0.666670;0.800000;,
  0.833330;0.800000;,
  1.000000;0.800000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.200000;0.000000;,
  0.200000;0.166670;,
  0.000000;0.166670;,
  0.400000;0.000000;,
  0.400000;0.166670;,
  0.600000;0.000000;,
  0.600000;0.166670;,
  0.800000;0.000000;,
  0.800000;0.166670;,
  1.000000;0.166670;,
  0.200000;0.333330;,
  0.000000;0.333330;,
  0.400000;0.333330;,
  0.600000;0.333330;,
  0.800000;0.333330;,
  1.000000;0.333330;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.666670;,
  0.000000;0.666670;,
  0.400000;0.666670;,
  0.600000;0.666670;,
  0.800000;0.666670;,
  1.000000;0.666670;,
  0.200000;0.833330;,
  0.000000;0.833330;,
  0.400000;0.833330;,
  0.600000;0.833330;,
  0.800000;0.833330;,
  1.000000;0.833330;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
