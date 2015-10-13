#include"DrawingFunc.h"

void DrawCircRing(GLdouble Ox, GLdouble Oy,GLdouble Radius, GLint SpliceNum)
{
	glColor3f(1, 0, 0);//set the color
	glPointSize(5);// set point size
	
	// generate the vertex array
	GLdouble ThetaStep = 2*Pi / SpliceNum;
	GLdouble *VertexX = new GLdouble[SpliceNum+2];
	GLdouble *VertexY = new GLdouble[SpliceNum+2];
	VertexX[0] = Ox; VertexY[0] = Oy;//add the circle origin
	for (int i = 1; i <= SpliceNum; i++)
	{
		VertexX[i] = Ox + Radius*cos(ThetaStep*(i - 1));
		VertexY[i] = Oy + Radius*sin(ThetaStep*(i - 1));
	}
	VertexX[SpliceNum + 1] = VertexX[1]; VertexY[SpliceNum + 1] = VertexY[1];//add the final vertex

	glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i <= SpliceNum+1; i++)
		{
			glVertex2f(VertexX[i], VertexY[i]);
		}

	glEnd();

	// free storage
	delete VertexX;
	delete VertexY;

	glFlush(); //update the display
}

void DrawCircTrunCone(GLdouble Ox, GLdouble Oy, GLdouble RadiusUpper, GLdouble RadiusLower, GLdouble Height, GLint SpliceNum)
{
	// Rotate the view for better displaying
	glRotatef(0.01, 0, 1, 0);
	glColor3f(1, 0, 0);//set the color
	glPointSize(5);// set point size
    // generate the vertex array
	GLdouble ThetaStep = 2 * Pi / SpliceNum;
	// Vertices of upper circ
	GLdouble *UpperVertexX = new GLdouble[SpliceNum+2];
	GLdouble *LowerVertexX = new GLdouble[SpliceNum+2];
	GLdouble *UpperVertexY = new GLdouble[SpliceNum+2];
	GLdouble *LowerVertexY = new GLdouble[SpliceNum+2];
	GLdouble *UpperVertexZ = new GLdouble[SpliceNum+2];
	GLdouble *LowerVertexZ = new GLdouble[SpliceNum+2];

	//Set origin
	GLdouble Oz = 0;// default as 0
	LowerVertexX[0] = Ox; LowerVertexY[0] = Oy; LowerVertexZ[0] = Oz;
	UpperVertexX[0] = Ox; UpperVertexX[0] = Oy; UpperVertexZ[0] = Oz + Height;
	// Generate other vertices
	for (int i = 1; i <= SpliceNum; i++)
	{
		LowerVertexX[i] = Ox + RadiusLower*cos(ThetaStep*(i - 1));
		LowerVertexY[i] = Oy + RadiusLower*sin(ThetaStep*(i - 1));
		LowerVertexZ[i] = Oz;
		UpperVertexX[i] = Ox + RadiusUpper*cos(ThetaStep*(i - 1));
		UpperVertexY[i] = Oy + RadiusUpper*sin(ThetaStep*(i - 1));
		UpperVertexZ[i] = Height+Oz;
	}
	// Add final points
	LowerVertexX[SpliceNum + 1] = LowerVertexX[1];
	LowerVertexY[SpliceNum + 1] = LowerVertexY[1];
	LowerVertexZ[SpliceNum + 1] = LowerVertexZ[1];
	UpperVertexX[SpliceNum + 1] = UpperVertexX[1];
	UpperVertexY[SpliceNum + 1] = UpperVertexY[1];
	UpperVertexZ[SpliceNum + 1] = UpperVertexZ[1];
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 1; i <= (SpliceNum + 1)*2; i++)
	{
		if (i%2==1)
		{
			glVertex3f(LowerVertexX[(i + 1) / 2], LowerVertexY[(i + 1) / 2], LowerVertexZ[(i + 1) / 2]);
		}
		else
		{
			glVertex3f(UpperVertexX[i / 2], UpperVertexY[i / 2], UpperVertexZ[i / 2]);
		}
	}

	glEnd();

	// free storage
	delete LowerVertexX;
	delete LowerVertexY;
	delete LowerVertexZ;
	delete UpperVertexX;
	delete UpperVertexY;
	delete UpperVertexZ;

	glFlush(); //update the display
}

void DrawSphere(GLdouble Ox, GLdouble Oy, GLdouble Oz, GLdouble Radius,GLdouble LowerRange, GLdouble UpperRange, GLint LongtitudeSpliceNum, GLint LatitudeSpliceNum)
{
	// Rotate the view for better displaying
	glRotatef(0.01, 0, 1, 0);
	glColor3f(1, 0, 0);//set the color
	glPointSize(5);// set point size

	// generate the vertex array
	GLdouble LowerTheta = LowerRange;
	GLdouble UpperTheta = UpperRange;
	GLdouble ThetaStep = (UpperTheta-LowerTheta) / LongtitudeSpliceNum;
	GLdouble PhiStep = 2 * Pi / LatitudeSpliceNum;
	// Generate theta list
	GLdouble *ThetaList = new GLdouble[LongtitudeSpliceNum];

	for (int i = 0; i < LongtitudeSpliceNum; i++)
	{
		ThetaList[i] = LowerTheta + i*ThetaStep;
	}
	ThetaList[LongtitudeSpliceNum - 1] = UpperTheta;
	// Generate phi list
	GLdouble *PhiList = new GLdouble[LatitudeSpliceNum+1];

	for (int i = 0; i < LatitudeSpliceNum; i++)
	{
		PhiList[i] = i*PhiStep;
	}
	PhiList[LatitudeSpliceNum] = PhiList[0];

	glBegin(GL_TRIANGLE_STRIP);
	int cnt = 0;
	for (int i = 0; i < LongtitudeSpliceNum ; i++)
	{
		//Loop through each theta
		for (int j = 0; j <= LatitudeSpliceNum; j++)
		{
			//Loop through each phi 
			// alternaltively add vertex
			if (cnt % 2 == 0)
			{
				glVertex3f(Ox + Radius*sin(ThetaList[i])*cos(PhiList[j]), Oy + Radius*sin(ThetaList[i])*sin(PhiList[j]), Oz + Radius*cos(ThetaList[i]));
			}
			else
			{
				glVertex3f(Ox + Radius*sin(ThetaList[i+1])*cos(PhiList[j]), Oy + Radius*sin(ThetaList[i+1])*sin(PhiList[j]), Oz + Radius*cos(ThetaList[i+1]));
				j--;
			}
			cnt++;
		}
	}
	glEnd();

	// free storage
	delete ThetaList;
	delete PhiList;

	glFlush(); //update the display
}

void DrawCircRing3D(GLdouble Ox,GLdouble Oy, GLdouble Oz,GLdouble RingRadius, GLdouble SectionRadius,GLdouble LowerRange, GLdouble UpperRange, GLint RingSpliceNum, GLint SectionSpliceNum)
{
	// Rotate the view for better displaying
	glRotatef(0.01, 0, 1, 0);
	glColor3f(1, 0, 0);//set the color
	glPointSize(5);// set point size
    // generate the vertex array
	GLdouble LowerTheta = LowerRange;
	GLdouble UpperTheta = UpperRange;
	GLdouble ThetaStep = (UpperTheta - LowerTheta) / RingSpliceNum;
	GLdouble PhiStep = 2 * Pi / SectionSpliceNum;
	// Generate theta list
	GLdouble *ThetaList = new GLdouble[RingSpliceNum];

	for (int i = 0; i < RingSpliceNum; i++)
	{
		ThetaList[i] = LowerTheta + i*ThetaStep;
	}
	ThetaList[RingSpliceNum - 1] = UpperTheta;
	// Generate phi list
	GLdouble *PhiList = new GLdouble[SectionSpliceNum + 1];

	for (int i = 0; i < SectionSpliceNum; i++)
	{
		PhiList[i] = i*PhiStep;
	}
	PhiList[SectionSpliceNum] = PhiList[0];

	glBegin(GL_TRIANGLE_STRIP);
	int cnt = 0;
	for (int i = 0; i < RingSpliceNum; i++)
	{
		//Loop through each theta
		for (int j = 0; j <= SectionSpliceNum; j++)
		{
			//Loop through each phi 
			// alternaltively add vertex
			if (cnt % 2 == 0)
			{
				glVertex3f(Ox + RingRadius*cos(ThetaList[i]) + SectionRadius*cos(PhiList[j])*cos(ThetaList[i]),Oy+RingRadius*sin(ThetaList[i]) + SectionRadius*cos(PhiList[j])*sin(ThetaList[i]), Oz+SectionRadius*sin(PhiList[j]));
			}
			else
			{
				glVertex3f(Ox + RingRadius*cos(ThetaList[i+1]) + SectionRadius*cos(PhiList[j])*cos(ThetaList[i+1]), Oy + RingRadius*sin(ThetaList[i+1]) + SectionRadius*cos(PhiList[j])*sin(ThetaList[i+1]), Oz + SectionRadius*sin(PhiList[j]));
				j--;
			}
			cnt++;
		}
	}
	glEnd();

	// free storage
	delete ThetaList;
	delete PhiList;

	glFlush(); //update the display
}

void DrawSpring3D(GLdouble Sx, GLdouble Sy, GLdouble Sz, GLdouble SpringRadius, GLdouble Length, GLdouble Period, GLdouble Thickness, GLint SpringSpliceNum, GLint SectionSpliceNum)
{
	// Rotate the view for better displaying
	glRotatef(0.01, 0, 1, 0);
	glColor3f(1, 0, 0);//set the color
	glPointSize(5);// set point size
				   // generate the vertex array
	GLdouble LowerTheta = 0;
	GLdouble UpperTheta = 2*Pi*Period;
	GLdouble ThetaStep = (UpperTheta - LowerTheta) / SpringSpliceNum;
	GLdouble PhiStep = 2 * Pi / SectionSpliceNum;
	// Generate theta list
	GLdouble *ThetaList = new GLdouble[SpringSpliceNum];

	for (int i = 0; i < SpringSpliceNum; i++)
	{
		ThetaList[i] = LowerTheta + i*ThetaStep;
	}
	ThetaList[SpringSpliceNum - 1] = UpperTheta;
	// Generate phi list
	GLdouble *PhiList = new GLdouble[SectionSpliceNum + 1];

	for (int i = 0; i < SectionSpliceNum; i++)
	{
		PhiList[i] = i*PhiStep;
	}
	PhiList[SectionSpliceNum] = PhiList[0];

	glBegin(GL_TRIANGLE_STRIP);
	int cnt = 0;
	for (int i = 0; i < SpringSpliceNum-1; i++)
	{
		//Loop through each theta
		for (int j = 0; j <= SectionSpliceNum; j++)
		{
			//Loop through each phi 
			// alternaltively add vertex
			if (cnt % 2 == 0)
			{
				glVertex3f(Sx + SpringRadius*cos(ThetaList[i]) + Thickness*cos(PhiList[j])*cos(ThetaList[i]), Sy + SpringRadius*sin(ThetaList[i]) + Thickness*cos(PhiList[j])*sin(ThetaList[i]), Sz + Length/SpringSpliceNum*i+Thickness*sin(PhiList[j]));
			}
			else
			{
				glVertex3f(Sx + SpringRadius*cos(ThetaList[i+1]) + Thickness*cos(PhiList[j])*cos(ThetaList[i+1]), Sy + SpringRadius*sin(ThetaList[i+1]) + Thickness*cos(PhiList[j])*sin(ThetaList[i+1]), Sz + Length / SpringSpliceNum*(i+1) + Thickness*sin(PhiList[j]));
				j--;
			}
			cnt++;
		}
	}
	glEnd();

	// free storage
	delete ThetaList;
	delete PhiList;
	glFlush(); //update the display
}