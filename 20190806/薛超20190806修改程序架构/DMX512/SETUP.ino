




void setup()
{
  Serial1.begin(9600);
  for (int i = 0; i < CHANNELNUM; i++)
  {
    DmxSimple.write (i, 0);
  }
}
