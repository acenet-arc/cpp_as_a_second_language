---
layout: page
title: Setup
permalink: /setup/
---

We will be working on a Compute Canada (CC) or virtual cluster with all the tools we will need already installed. You will need a method of connecting to either a CC cluster, or our virtual cluster, which means you will need a method of connecting to them using [SSH](https://docs.computecanada.ca/wiki/SSH). SSH can be used from a terminal which we explain how to install and open in the **Ensure you can open a terminal** section below.

# Compute Canada Account
If you already have a Compute Canada account you can log into a CC cluster to follow along. A CC account will allow you to continue to use the same environment that you used during the workshop after the workshop has completed.
* Graham: `graham.computecanada.ca`
* Cedar: `cedar.computecanada.ca`
* Béluga: `beluga.computecanada.ca`

### Don't have a Compute Canada account?
For those who do not have a CC account, we will provide a virtual cluster that you can use during the workshop, however you will loose access to it shortly after.

# Ensure you can open a terminal
The only setup required on your laptop is ensuring you can open a Linux command line terminal.

### Windows
[MobaXterm](http://mobaxterm.mobatek.net/) is recommended for Windows computers. Download and install MobaXterm **home installer edition**. The portable version will not keep files from one session to the next. Verify you can run mobaXterm and "start local terminal".

### Mac/Linux
You already have a terminal built in.

To see how to open your terminal on your **Mac** see this [youtube video](https://www.youtube.com/watch?v=zw7Nd67_aFw).

If you are a **Linux** user running Ubuntu, the first 30 seconds of this [youtube video](https://www.youtube.com/watch?v=_xUvH2iRizU) shows you how to access the terminal. If you are having trouble accessing a terminal on your laptop before you arrive we can help you at the beginning of the workshop.

# Test your ssh connection

### If using a CC account
If you are using your CC account make sure you can connect to one of the CC clusters mentioned above. To connect to the Graham cluster for example you would use the command below.
~~~
$ ssh graham.computecanada.ca
~~~
{: .bash}

### If using our virtual cluster
Try connecting to our virtual training cluster by running the below command in your terminal.
~~~
$ ssh user01@nova.ace-net.training
~~~
{: .bash}
You should get prompted for a password. Press Ctrl+C to exit without supplying a password. We will provide one for you at the beginning of the workshop.
