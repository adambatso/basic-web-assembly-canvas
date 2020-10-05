int isPrime(int number) {
            for( int num = 2; num< number; num++) {
                if (number % num == 0) { return 0;}
            }
            return 1;
        } 

        int countPrimes( int numberOfIteration) {
            int count = 0;
            for(int prime = 0; prime <= numberOfIteration; prime++) {
                if (isPrime(prime)) {
                    count++;
                }
            } 
            return count;
        }