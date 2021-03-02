import datetime
# This is the Rule class, which handles firewall rules

class Rule:
    def __init__(self,entity,temp):
        """Constructor

        Args:
            entity ({Entity}): Hostile Entity to block
            temp ({bool}): Is the rule temporally
        """        
        self.date = datetime.datetime.now()
        self.ent = entity.get_mac_add()
        self.temp = temp 

    """
    This function returns the parameters for the iptables rule
    Input: none
    Output: the parameters : string
    """
    def write_rule(self):
        """
        This function returns the parameters for the iptables rule

        Returns:
            [str]: the rule parameters
        """        

        #return "-m mac --mac-source "+self.ent.get_mac_add()
        return " -s " + self.ent.get_ip_add()
        


    """getters functions""" 

    def is_temp(self):
        return self.temp
       
    def get_date(self):
        return self.date