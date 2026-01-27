int main() {

	int array[5] = {0,5,1,5,4};
	int i,v;

	i = input();

	v = array[i];

	// The bodies of these loops aren't important. I just 
	// added them to make it easy to distinguish them when
	// looking at the LLVM IR
	if(3 <= array[i]) {
		i = input() + 1;
	}
	else if(array[i] <= 4) {
		i = input() + 2 ;
	}
	else if(array[i] > 2) {
		i = input() + 3;
	}
	else if(array[i] == 4) {
		i = input(); 
	}
	else if(array[i] == 3 || array[i] == 2) {
		i = input() + 10;
		if(array[i] == 0 && array[i] == 3) {
			i = input() + 20;
		}
	}
	else {
		i = input() + 4;
	}

	return i;
}
