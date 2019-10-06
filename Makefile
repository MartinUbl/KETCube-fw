doc:
	doxygen Doxyfile
clean:
	rm docs/html/*
indent:
	@echo "Indenting files according to set rules ..."
	@./supportTools/indent.sh

indent_check:
	@echo "Checking files indentation according to set rules ..."
	@./supportTools/indent.sh detect
