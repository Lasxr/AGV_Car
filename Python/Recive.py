import paho.mqtt.client as mqtt

broker_address = "192.168.100.8"
broker_port = 1883
topic = "Topic/python/Test"

def on_connect(self,client,userdata,rc):
    print("MQTT Connected..")
    self.subscribe(topic)