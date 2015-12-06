#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>

template <typename T>
int getMaxIndex(std::vector<T> vec, int size){

    T maxValue = vec[0];
	int maxIndex = 0;
	for(int i = 0; i < size; i++){
        if(vec[i] > maxValue){
            maxValue = vec[i];
			maxIndex = i;
		}
	}	
	return maxIndex;
}

template <typename T>
int getMinIndex(std::vector<T> vec, int size){

    T minValue = vec[0];
    int minIndex = 0;
    for(int i = 0; i < size; i++){
        if(vec[i] < minValue){
            minValue = vec[i];
            minIndex = i;
        }
    }
    return minIndex;
}

template <typename T>
int getMax(std::vector<T> vec, int size){

    T maxValue = vec[0];

    for(int i = 0; i < size; i++){
        if(vec[i] > maxValue){
            maxValue = vec[i];
        }
    }
    return maxValue;
}

template <typename T>
int getMin(std::vector<T> vec, int size){

    T minValue = vec[0];

    for(int i = 0; i < size; i++){
        if(vec[i] < minValue){
            minValue = vec[i];
        }
    }
    return minValue;
}

#endif
