COP4600 Spring 2017
Programming Assignment 2 
Assignment Group 18


Character-mode Linux device driver as a kernel module: 
This character-mode driver stores bytes to a buffer and removes them from the buffer as they are read out in FIFO order. 

Instructions:
	>> make				# execute the Makefile 
	>> sudo insmod testdev.ko	# load the module into the kernel 
	>> dmesg  			# to confirm that the device was added successfully 
	>> sudo ./test 			# use the provided userspace test program to test the kernel module (if desired)  
	>> sudo rmmod testdev 		# remove the module when finished
