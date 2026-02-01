SUBDIRS=toupper 
clean:
	rm -rf cfmse-experiments table3.csv toupper.csv
	$(foreach dir, $(SUBDIRS), make -C $(dir) force_clean;)


