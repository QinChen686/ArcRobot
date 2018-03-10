#include "stdafx.h"
#include "glDisplay.h"
using namespace std;
int glDisplay::ReadSlpFile()
{
	char buffer[256];
	ifstream slpin("C:\\Users\\QC\\Desktop\\论文\\OpenGl\\SLPData_IRB1410\\irb1400_-_m2000_rev2_01-1.slp");
	if (!slpin.is_open())
	{
		cout << "Error opening file"; 
		exit(1);
	}
	int normalCount = 0;
	while (!slpin.eof())
	{
		slpin.getline(buffer, 100);
		if (strncmp(buffer, "      normal", 12) == 0)
		{
			sscanf_s(buffer, "      normal %lf %lf %lf", &NorverVec[count].normal1, &NorverVec[count].normal2, &NorverVec[count].normal3);
			cout << "THE " << count << "TH normal is " << NorverVec[count].normal1 << "  " << NorverVec[count].normal2 << "	" << NorverVec[count].normal3 << endl;
			count++;
			normalCount++;
		}
		if (strncmp(buffer, "      vertex", 12) == 0)
		{
			if (normalCount == 3)
			{
				normalCount = 0;
				count -= 3;
			}
			sscanf_s(buffer, "      vertex %lf %lf %lf", &NorverVec[count].vertex1, &NorverVec[count].vertex2, &NorverVec[count].vertex3);
			cout << "THE " << count << "TH vertex is " << NorverVec[count].vertex1 << "  " << NorverVec[count].vertex2 << "  " << NorverVec[count].vertex3 << endl;
			count++;
		}
	}
	return 0;
}

void glDisplay::GLDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*NewView = *NewEye*-1;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(TempTranslateVec->X(), TempTranslateVec->Y(), TempTranslateVec->Z());
	glScalef(TempscaleFactor, TempscaleFactor, TempscaleFactor);
	gluLookAt(NewEye->X(), NewEye->Y(), NewEye->Z(),
		NewView->X(), NewView->Y(), NewView->Z(),
		NewUp->X(), NewUp->Y(), NewUp->Z());

	/////////////////////////////////////////////////
	//定义材质
	GLfloat robot_mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  //定义材质的环境光颜色，骗蓝色  
	GLfloat robot_mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  //定义材质的漫反射光颜色，偏蓝色  
	GLfloat robot_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //定义材质的镜面反射光颜色，红色  
	GLfloat robot_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0  
	GLfloat robot_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, robot_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robot_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robot_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, robot_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, robot_mat_shininess);
	////////////////////////////////////////////////

	////////////////////////////////////////////////
	glBegin(GL_TRIANGLES); // Drawing Using Triangles 
	glColor3f(1, 1, 1);
	for (int i = 0; i != count; i++)
	{
		glNormal3f(NorverVec[i].normal1, NorverVec[i].normal2, NorverVec[i].normal3);
		glVertex3f(NorverVec[i].vertex1, NorverVec[i].vertex2, NorverVec[i].vertex3);
	}
	glEnd();           // Finished Drawing The Triangle 
	////////////////////////////////////////////////
	//SwapBuffers(hrenderDC);
}

void glDisplay::executeRotateOperation(int x, int y)
{
	Mouse->setX(x);
	Mouse->setY(y);

	Vector3D MouseTrace = *AuxY*(OldMouse->Y() - Mouse->Y()) + *AuxX*(Mouse->X() - OldMouse->X());
	Vector3D RotateAsix = Vector3D::crossProduct(MouseTrace, *AuxZ);
	RotateAsix.normalize();

	float angle = MouseTrace.length();
	Matrix4D rotatMatrix = Matrix4D::getRotateMatrix(angle, RotateAsix);

	*NewEye = rotatMatrix*(*NewEye);
	*NewUp = rotatMatrix*(*NewUp);

	NewUp->normalize();
	*AuxY = *NewUp;
	*AuxZ = (Vector3D)*NewEye - (Vector3D)*NewView;
	*AuxX = Vector3D::crossProduct(*AuxY, *AuxZ);
	AuxX->normalize();
	*OldMouse = *Mouse;
}
void glDisplay::executeScaleOperation(float factor)
{
	if (TempscaleFactor <= 0)
	{
		TempscaleFactor = 0.1;
	}
	else
	{
		TempscaleFactor += factor;
	}
}

void glDisplay::executeTranslateOperation(int x, int y)
{
	Mouse->setX(x);
	Mouse->setY(y);
	Vector3D vec(-OldMouse->X() + Mouse->X(), -Mouse->Y() + OldMouse->Y(), 0);
	*TempTranslateVec = *TempTranslateVec + vec;
	*OldMouse = *Mouse;
}

void glDisplay::getInitPos(int x, int y)
{
	Mouse->setX(x);
	Mouse->setY(y);
	*OldMouse = *Mouse;
}
