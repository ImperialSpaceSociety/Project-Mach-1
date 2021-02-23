
int isNumeric (const char *s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

void readGps(long *latitude, long *longitude, long *altitude) {
  *latitude = ubloxGps.getLatitude();
  *longitude = ubloxGps.getLongitude();
  *altitude = ubloxGps.getAltitude();
}
