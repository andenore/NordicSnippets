from pynrfjprog import API, Hex
import unittest
import sys
import os


DIR = os.path.dirname(os.path.realpath(sys.argv[0]))
FILENAME = os.path.join(DIR, 'armgcc/nvmc.hex')

class NVMCTests(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.device_family = API.DeviceFamily.NRF51  # Start out with nRF51 as expected target device, will be checked and changed if target is an nRF52 series device.
        self.api = API.API(self.device_family)
        
        self._connect_to_target()
        
        self.device_version = self.api.read_device_version() # Check our assumption that the target was an nRF51 series device.
        if 'NRF52' in self.device_version: # If target is an nRF52 series device reconnect w/ correct device parameters.
            self.device_family = API.DeviceFamily.NRF52
            self.api.close()
            self._connect_to_target()

        self.api.recover() # Erase all Flash, RAM and disable any protection before running test suite.
        
    @classmethod
    def tearDownClass(self):
        self.api.recover()
        self.api.disconnect_from_emu()
        self.api.close()
        
    def setUp(self):
        pass
        
    def tearDown(self):
        self.api.erase_all()

    def test_erase_code_flash(self):
        test_address = 0x20000
        test_data    = 0xDEADBEEF
        
        self.api.write_u32(test_address, test_data, 1)
        
        self._program_hex_file_and_run(FILENAME)
        
        expectedData = 0xFFFFFFFF
        readData     = self.api.read_u32(test_address)
        
        self.assertEqual(expectedData, readData)

    def test_erase_uicr_flash(self):
        test_address = 0x10001080
        test_data    = 0xDEADBEEF
        
        self.api.write_u32(test_address, test_data, 1)
        
        self._program_hex_file_and_run(FILENAME)
        
        expectedData = 0xFFFFFFFF
        readData     = self.api.read_u32(test_address)
        
        self.assertEqual(expectedData, readData)

    
    @classmethod    
    def _connect_to_target(self):
        """
        Initialzes and connects self.api to target. self.api can now perform operations on connected device.
        """
        self.api.open() 
        self.api.connect_to_emu_without_snr()
        self.api.connect_to_device()

    @classmethod
    def _program_hex_file_and_run(self, hex_file_path):
        """
        Programs hex_file to the target device, reset, and run the application.
        """
        data = Hex.Hex(hex_file_path)
        for segment in data:
            self.api.write(segment.address, segment.data, True)

        self.api.sys_reset()
        self.api.go()


unittest.main(verbosity = 2) # Call the unit tests with desired verbosity.
