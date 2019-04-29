/*
Name:Zhenjiang Yang
Student Number:001431873
MacID: yangz5
*/
#ifndef __MESH_H__
#define __MESH_H__

class Mesh {
public:
	Mesh();
	float** pointsMap;
	void multiplePoints(int size);
	void drawPolygon();
	void drawTri();
	void drawTriLine();
	void circles(int centerx, int centerz, int circleSize, int height);
	void drawLineLoop();
	int size;
	void random(int a, int b, int number);

};

#endif
