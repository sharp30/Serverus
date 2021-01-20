
import os
from crontab import CronTab
import datetime
import socket
import time
import threading

from datetime import datetime

import Rule
import Event
import Log


COMPUTER_ID = 1
# This is the Defender class, which will execute the defensive actions against hostile entities.

class Defender():

    count = 0 #amount of objects created

    def __init__(self):
        """Constructor

        Raises:
            Exception: If a Defender object was already created
        """

        if Defender.count > 0:
            raise Exception("Cant create more than one Defender (Singletone Class)")

        self.events = []
        self.thread = threading.Thread(target=inform, args=(self))
        self.cron = CronTab(user="root")
        self.emerge = False #level 4 has been found
        
        try:
            self.log = Log.Log(input("Enter log file name: "))
        except Exception as e:
            raise e

        thread.start()


    def defend(self,event,local =False):
        """
        Primary function, provides the defence from hostile event, according to the anomaly level.
        Args:
            event ({event}): The hostile event the defend from
        """

        if not local:
            self.events += [event]

        self.__close_socket(self, event)

        if event.get_level() == 1:
            return

        rule = Rule.Rule(event)

        #for upgrading

        self.__block(event, rule)

        if event.get_level() == 4:
            self.emerge = True


    def cancel_action(self, event):
        """This function cancel fire-wall blocking

        Args:
            event ({Event}): which event to cancel the block for
        """
        ERROR_CODE = "256"
        msg = ""
        while str(msg).find(ERROR_CODE) < 0:
            msg = os.system("iptables -D INPUT %s -j DROP"%(Rule.Rule(event,3).write_rule()))
        self.log.add_unblock_record(event)



    def __close_socket(self, event):
        """The function closes a specific socket

        Args:
            event ({Event}): Hostile event
        """
        #terminates all sockets with event
        os.system("ss --kill -nt dst %s "%(event.get_ip_add()))
        self.log.add_block_record(event,1)

    


    def __block(self, rule):

        """This function blocks an event at the firewall

        Args:
            rule ({Rule}): The rule to write in the firewall
        """


        RULE_NOT_FOUND = 256
        #check if rule already exists
        try:
            if int(os.system("iptables -C INPUT %s -j DROP"%(rule.write_rule()))) != RULE_NOT_FOUND:
                #rule already exists
                if not rule.is_temp():
                    self.__delete_cron(rule.write_rule())
                return

        except Exception as e:
            self.log.add_error_record(e)


        if rule.is_temp():
            time_to_delete = rule.get_date() + datetime.timedelta(minutes=2) #time to disable blocking
            rule_to_write = "/sbin/iptables -D INPUT %s -j DROP"%(rule.write_rule())

            job = self.cron.new(command = rule_to_write +"; crontab -l | grep \"" +rule_to_write + "\" | crontab -r")
            job.setall("%d %d * * *"%(time_to_delete.minute,time_to_delete.hour))
            self.cron.write()

            #self.log.add_block_record(event, 2)
        #else:
        #self.log.add_block_record(event, 3)


        os.system("/sbin/iptables -A INPUT %s -j DROP"%(rule.write_rule()))


    def __delete_cron(self,data):
        """
        This function deletes a cron from the crontab lists

        Args:
            data ({str}): The cron action - the data of the cron
        """
        for job in self.cron:
            print(job.command)
            if data in job.command:
                self.cron.remove(job)
        self.cron.write()


    def __inform(self):
        """[summary]

        Args:
        """

        while True:
            start = datetime.now().time()
            while not found and  (datetime.now().time() - start).minutes <= 10:
                time.sleep(10) #sleep 10 seconds
            found = False

            message = bytearray(COMPUTER_ID)
            for i in self.events:
                message += i.to_packet()
            #requires lock
            events = []
            #get all events to send
            data = bytearray()
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((HOST, PORT))
                s.sendall(message)
                data = s.recv(1024)
            
            #block events from global server
            for i in range(len(data)::6):
                self.defend(data[i:i+6],local=True) #at level3

        

def main():    
    defender= Defender()
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_address = ("127.0.0.1", SERVER_PORT)
    sock.connect(server_address)
    while True:
        msg_answer = sock.recv(1024)
        defender.defend(Event.Event(msg_answer))

if __name__ == '__main__':
    main()