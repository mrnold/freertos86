.PHONY: demo powerctl democlean powerctlclean

all: demo powerctl

clean: democlean powerctlclean
	python -c "import shutil; shutil.rmtree('$(BUILD)/apps', True)"

demo:
	make -C demo

powerctl:
	make -C powerctl

democlean:
	make -C demo clean

powerctlclean:
	make -C powerctl clean
