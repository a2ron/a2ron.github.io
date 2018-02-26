# Ansible playbook for Alexa

Next playbook helps to install Alexa following [this guide][alexa-pi-repo]. 

You can download it [here][alexa-playbook-src].

- Clone the repo running

```
git clone https://github.com/a2ron/domotics-ansible-setup.git
```

- Create your inventory file (hosts.inventory) 📃

```
[hosts]
<HOST>:<PORT> ansible_ssh_user=<USER>
```

- Create Alexa Device [config file][alexa-device-config-file] (config.txt) 📃

```
CLIENT_SECRET=""
#NOTE: The Device Serial Number can be any unique number
DEVICE_SERIAL_NUMBER="123456"
CLIENT_ID=""
PRODUCT_ID=""
```
- Launch the playbook 💻

```
ansible-playbook -i hosts.inventory alexa.yml 
 ```




[alexa-pi-repo]:https://github.com/alexa/avs-device-sdk/wiki/Raspberry-Pi-Quick-Start-Guide-with-Script
[alexa-playbook-src]:https://github.com/a2ron/domotics-ansible-setup/blob/master/alexa.yml
[alexa-device-config-file]: https://github.com/a2ron/domotics-ansible-setup/tree/master/files/alexa/config-sample.txt