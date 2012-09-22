METAR2MQTT
==========

Move and parse METAR data from weather.noaa.gov and publish it in your MQTT server.


About METAR 
===========

* http://en.wikipedia.org/wiki/METAR
* http://www.wunderground.com/metarFAQ.asp


Locate a station 
================

* http://www.nws.noaa.gov/tg/siteloc.shtml


Examples 
========

Koebenhavn / Kastrup / EKCH
* http://weather.noaa.gov/pub/data/observations/metar/stations/EKCH.TXT

Malmo / Sturup / ESMS
* http://weather.noaa.gov/pub/data/observations/metar/stations/ESMS.TXT

Kristianstad / Everod / ESMK 	  	
* http://weather.noaa.gov/pub/data/observations/metar/stations/ESMK.TXT


Testdata 
========

In another project I have saved the METAR data from those stations, 
and the data is included in the testdir in xml format so the tests will have some realistic input.

But please note that it is quite a lot of data, 
if we look at EKCH we have data from 
2004-10-10 07:50:00 up to 2012-09-21 17:50:00 saved every 30min.
So I think it is 135097 data points.


METAR Decoder Software Package Library
======================================

* http://limulus.net/mdsplib/
* http://mdsplib.sourceforge.net/
* https://sourceforge.net/projects/mdsplib/

