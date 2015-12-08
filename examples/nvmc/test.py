from pynrfjprog import API, Hex
import unittest

class NVMCTests(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.device_family = API.DeviceFamily.NRF51  # Start out with nRF51, will be checked and changed if target device is nRF52.
        self.api = API.API(self.device_family)
        
        self._connect_to_target()
        
        self.device_version = self.api.read_device_version() # Check our assumption that the target was an nRF51 series device.
        if 'NRF52' in self.device_version:
            self.device_family = API.DeviceFamily.NRF52 # If target is an nRF52 series device reconnect w/ correct device parameters.
            self.api.close()
            self._connect_to_target()

        self.api.recover() # Erase all Flash, RAM and disable protection if chip is protection before running test suite.
        
    @classmethod
    def tearDownClass(self):
        self.api.recover()
        self.api.disconnect_from_emu()
        self.api.close()
        
    def setUp(self):
        pass
        
    def tearDown(self):
        pass

    def test1(self):
        print('Hey')
        
    def _connect_to_target(self):
        self.api.open() 
        self.api.connect_to_emu_without_snr()
        self.api.connect_to_device()


unittest.main(verbosity = 2) # Call the unit tests with desired verbosity.