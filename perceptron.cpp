# include <bits/stdc++.h>
#define SIZE 4
using namespace std;


class Perceptron{
	vector <int> x_train[SIZE];
	int epoch;
	float learn_rate;
	float accuracy = 0;
	float samples;
	float bias = 0;
	vector<float> weights;
	bool logOutput;
	public:
		Perceptron(vector <int> cx_train[SIZE], int cepoch = 10, float clearn_rate = 0.2, bool logVerbose = false): weights(cx_train[0].size()) {
			for(int i = 0; i<SIZE; i++){
				x_train[i].assign(cx_train[i].begin(), cx_train[i].end());
			}				
			epoch = cepoch;
			learn_rate = clearn_rate;
			logOutput = logVerbose;
			
			for(int i=0; i< cx_train[0].size(); i++){
				weights[i] = randomFloat(1.0, 2.0);
			}				
		}
		int activationFunction(float x){
			if(x >= 0) return 1;
			else return 0;	
		}
		float randomFloat(float a, float b) {
		    float random = ((float) rand()) / (float) RAND_MAX;
		    float diff = b - a;
		    float r = random * diff;
		    return a + r;
		}
		float current_accuracy(){
			float x = (float)(accuracy/samples);
			return x;
		}
		int predictOutput(vector<int>input){
			float total = bias;
			for(int i=0; i<input.size(); i++){
				total += (float)(weights[i] * input[i]);
			}
			return activationFunction(total);
		}
		
		void train(vector<int>y_train){
			for(int i=0; i<epoch; i++){
				for(int j =0; j<SIZE; j++){
					int prediction = predictOutput(x_train[j]);
					if(logOutput) cout<<"Expected: "<< y_train[j] <<"\tOUTPUT: "<<prediction<<endl; 
					if(y_train[j] == prediction){
						accuracy +=1.0;
					}
					else{
						accuracy -=1.0;
					}
					samples++;
					// calculate losses
					
					int loss = y_train[j] - prediction;
					
					//update weights
					for(int w = 0; w<x_train[j].size(); w++){
						weights[w] += (float) (loss * learn_rate * x_train[j][w]); 
					}
					bias += (float) loss * learn_rate;
				}
				if(logOutput){
					cout<<"Current Accuracy: "<<current_accuracy()<<endl;
					cout<<endl;	
				}

			}
		}
		void getCurrentWeight(){
			for(int i=0; i<x_train[0].size(); i++){
				cout<<weights[i]<<endl;
			}
		}	
};

int main(){
	vector <int> train_test[SIZE];
	train_test[0] = {1,1};
	train_test[1] = {0,1};
	train_test[2] = {1,0};
	train_test[3] = {0,0};
	vector <int> and_train_set{1,0,0,0};
	vector <int> or_train_set{1,1,1,0};
	int predict;
	string operation;
	vector<int>test_train_set(2);
	string logOutput;
	cout<<"Do you want to see the training output(y/N)"<<endl;
	cin>>logOutput;
	Perceptron p(train_test, 1000, 0.3, logOutput== "y" ? true: false);
	cout<<"Enter the logical operation you want to perform(OR/AND)"<<endl;
	cin>>operation;
	cout<<"Enter the two values you want to test "<<endl;
	int x, y;
	cin>>x>>y;
	test_train_set.push_back(x);
	test_train_set.push_back(y);
	predict  = p.predictOutput(test_train_set);
	cout<<"Test prediction before training: "<<predict<<endl;
	p.train(operation == "OR" ? or_train_set : and_train_set);
	predict  = p.predictOutput(test_train_set);
	cout<<"Test predition after training: "<<predict<<endl;
	
	
}
