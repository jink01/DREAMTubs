import glob
import os
import sys

mrgpath = "/eos/user/i/ideadr/TB2021_Desy/mergedNtuple/"
recpath = "/eos/user/i/ideadr/TB2021_Desy/recoNtuple_20220307/"

myconf = str(sys.argv[1])
print myconf

my_list0 = ["71","73","74","75","76","77","78","79","80","81","82","83","84","85","86"]
 
my_list1 = ["108","113","116","117","118","119","120","121","122","132","180","182", "183", "184","185","186","187","188","189", "190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","207","208","209","228","229","230","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230"]

my_list2 = ["266","267","268","269","298","271","272","273","274","275","276","277","278","279","280","281","290","291","292","293","294","295","296","389","390","391","392","393","394","395","396"]

if myconf =="0":
   mylist = my_list0
if myconf =="1":
   mylist = my_list1
if myconf =="2":
   mylist = my_list2

print mylist

for fl in mylist:
	cmnd1 = "root -l -b -q .x 'PhysicsConverter.C(\""+fl+"\"," + myconf + ")'"
	os.system(cmnd1)

