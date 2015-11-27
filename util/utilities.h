#ifndef UTILITIES_H
#define UTILITIES_H

template <typename T>
int getMaxIndex(T* array, int size){

	T maxValue = array[0];
	int maxIndex = 0;
	for(int i = 0; i < size; i++){
		if(array[i] > maxValue){
			maxValue = array[i];
			maxIndex = i;
		}
	}	
	return maxIndex;
}



#endif
