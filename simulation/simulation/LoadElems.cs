﻿using Newtonsoft.Json;

namespace simulation
{
    [JsonObject(MemberSerialization.OptIn)]
    public class LoadedElems : Observable
    {
        private string _Name;

        private LoadedElem[] _elems;

        public LoadedElems()
        {
            Name = "";
        }

        [JsonProperty]
        public string Name { get { return _Name; } set { _Name = value; RaisePropertyChanged("Name"); } }

        [JsonProperty]
        public LoadedElem[] elems { get { return _elems; } set { _elems = value; RaisePropertyChanged("elems"); } }
    }
    [JsonObject(MemberSerialization.OptIn)]
    public class LoadedElem : Observable
    {
        public LoadedElem()
        {
            Id = 0;
            Load = new double[][] { };
        }

        private int _Id;

        [JsonProperty]
        public int Id { get { return _Id; } set { _Id = value; RaisePropertyChanged("Id"); } }

        private loadType _lType;

        [JsonProperty]
        public loadType lType { get { return _lType; } set { _lType = value; RaisePropertyChanged("lType"); } }

        private loadDirect _lDirect;

        [JsonProperty]
        public loadDirect lDirect { get { return _lDirect; } set { _lDirect = value; RaisePropertyChanged("lDirect"); } }

        private double[][] _Load;

        [JsonProperty]
        public double[][] Load { get { return _Load; } set { _Load = value; RaisePropertyChanged("Load"); } }
    }


}