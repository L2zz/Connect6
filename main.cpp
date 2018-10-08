#include<stdio.h>
#include "network.cpp"
#include "eval.cpp"
void get10index(char* state, float* UCT, int lastAction, int* indexes, float* W1, float* b1, float* W2, float* b2, Network network); //��,  UCT = R + sqrt(log(n)/n_action), �ֱ� �׼�, best 10�� ���� array pointer 

int main(void){
	
	int inputsize = 11;
	int hiddensize = 10;
	int outputsize = 1;
	int batch = 4;
	// �̷��� 9���� ������  �˴ϴ�. 
	int lastAction = 180;
	char state[361];
	float UCT[361] = {0};  //��������� ���߿� ������ ���� 
	
	Network CalDeepUCT(batch, inputsize, hiddensize, outputsize); 
	float W1[inputsize * hiddensize] = {1,2,3,4,5,6,};	
	float b1[batch * hiddensize] = {2,3,4,4,5,6,7,7,2,1,2,3,4,4,5,6,7,7,2,1,2,3,4,4,5,6,7,7,2,1,2,3,4,4,5,6,7,7,2,1};
	float W2[hiddensize * outputsize] = {2,3,4,4,5,6,7,7,2,1};
	float b2[batch * outputsize] = {4,2,1,4};        // �̰Ŵ� CalDeepUCT �� �����Ҷ�  ��ü �ϳ� ������ָ�ǰ�, W1, b1, W2, b2�� ���� ���������� update ��  ����, ���� ��ȸ���� �н��� �Ķ���͸� ���ÿ� ����Ȱ� �ҷ��ͼ� �ʱ�ȭ�Ұ���                                      

	int indexes[10]; // �ư� best 10 ���� array 
	
	get10index(state, UCT, lastAction, indexes, W1, b1, W2, b2, CalDeepUCT);
	
	
	return 0;
}
 
void get10index(char* state, float* UCT, int lastAction, int* indexes, float* W1, float* b1, float* W2, float* b2, Network CalDeepUCT){
	float temp;
	float DeepUCT[361] = {0};
	
	initUCT(DeepUCT, state, lastAction, CalDeepUCT, W1, b1, W2, b2);
	
	updateUCT(DeepUCT, state, lastAction, CalDeepUCT, W1, b1, W2, b2);
	
	addUCT(DeepUCT, UCT);
	
	best10(DeepUCT, 10, indexes);
	/*
	for(int i =0; i<10; i++){
		printf("%d index : %d, value : %f\n",i, indexes[i], DeepUCT[indexes[i]]);	
	}
	*/	 
}

