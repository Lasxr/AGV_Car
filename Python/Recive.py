import paho.mqtt.client as mqtt

broker_address = "192.168.100.8"
broker_port = 1883
topic = "Network/Python/Car"

def on_connect(self,client,userdata,rc):
    print("MQTT Connected..")
    self.subscribe(topic)
    
def on_message(client,userdata,msg):
    print(msg.payload.decode("utf-8","strict"))
    
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)
client.on_connect = on_connect
client.on_message = on_message
client.connect(broker_address,broker_port)
client.loop_forever()
