doc:
	doxygen Doxyfile

doc_check:
	( cat Doxyfile ; echo "WARN_LOGFILE = DoxyWarnings.log" ) | doxygen -
	@[ -f DoxyWarnings.log ] && cat DoxyWarnings.log >&2
	@test ! -s DoxyWarnings.log

clean:
	rm docs/html/*

indent:
	@echo "Indenting files according to set rules ..."
	@./supportTools/indent.sh

indent_check:
	@echo "Checking files indentation according to set rules ..."
	@./supportTools/indent.sh detect
