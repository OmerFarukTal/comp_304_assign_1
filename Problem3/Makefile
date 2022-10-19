CC=gcc

final: driver consumer_producer
	
driver:
	$(CC) driver.c -o driver

consumer_producer:
	$(CC) consumer_producer.c -lrt -o consumer_producer
	
clean:
	rm ./driver ./consumer_producer
	
run: final
	./driver consumer_producer 3 Naber
	
runhard: final
	./driver consumer_producer 5 NABERLAN
