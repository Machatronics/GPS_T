void haversine()
{
  latitude1=(lat1*PI)/180;
  latitude2=(lat2*PI)/180;
  longitude1=(long1*PI)/180;
  longitude2=(long2*PI)/180;
  del_lat=latitude2-latitude1;
  del_long=longitude2-longitude1;
  var_a=((sin(del_lat/2))*(sin(del_lat/2)))+(cos(latitude1)*cos(latitude2)*sin(del_long/2)*sin(del_long/2));
  var_c = 2* atan2(sqrt(var_a),sqrt(1-var_a));
  var_d= Radius*var_c;
  
}
