//Overveiw
    This program provides guidance counsilers with a way to quickly provide thier incredibily large amount of students with classes they need, 
    show what classes are less than 30% full of students, classes that are completely full, and students that don't have enough credits. 
//The issue our program solves
    This project hopes to provide the much needed aid to guidance counselers that they need when dealing with an over abundance of students. 
    It provides then with a way to quickly comb through all the data they have access too and more effiencently provide students with the classes they need 
    while also giving them information to help the school they are employed for. Most times these guidance counsilers have way more students than time they
    can provide them. Our program is disgned to bridge that gap and make their jobs easier so they can do more than refer them to a pdf of all the classes 
    they need. Hopefully this makes students lives better as they are able to not feel like just another cog in the machine and instead like a Student
    attending a accredited college working towards a degree. 

//How users can get started with the project
    Users can get started by simply downloading the cpp and .h files in this repository. Users would then run our program with 2 CSV files.
    The first being CSV of classes (format: Name,Session Number,Credits,Capacity,MWF/TTh,TimeStart,TimeEnd,Prereqs) 
    The second being the CSV of students (format: Name,Year,Credits,Classes Taken)
    Users can then choose whether or not to include the name of the output file 
    After running the program users can expect output.csv (or "exampleFileName.csv) to be stored with the data written inside it
    The data will be sorted from student with the most credits to the least along with the classes they should be taking

//Users can get help by either looking through the documentation file or by contacting one of following:
    kashmore@uri.edu
    kishan_patel@uri.edu
    andrew_teh@uri.edu
    garrett_kemper@uri.edu
    
//Who maintains and contributes to the project
    Kishan Patel: Range Tree implementation, 
    Andrew Teh: main implementation
    Kamden Ashmore: flashsort, Student and Class objects, 
    Garrett Kemper: BloomFilter implementation, creation of test data sets, main implementation
        *for report contributions see the info page in the report folder (Reports/info.txt)
    
