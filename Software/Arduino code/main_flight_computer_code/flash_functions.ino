
void read_from_flash(uint32_t addr){
  dataPacket out;
  flash.readAnything(addr - PACKET_SIZE, out);
  print_info(&out);
}

bool write_info(dataPacket dp){
  if (flash.writeAnything(_addr, dp)){
    //increment address pointer
    _addr += PACKET_SIZE;

    return true;
  }
  else{
    Serial.print("Problem writing to flash.");
    return false;
  }
}

void dumpFlash(){
  int num_packets = _addr / PACKET_SIZE;
  for(int i = 1; i < num_packets; i++){
    read_from_flash(run_start + i * PACKET_SIZE);
  }
}
