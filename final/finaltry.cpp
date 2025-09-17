void HashTable::rehash()
{
    SongList *table2 = [table_slot_size*2];
    for (int i = 0; i < table_slot_size; i++)
    {
        //&(table2+i) = &(table+i);
        SongList current = table[i]->pop_head();
        while(curretn != nullptr){
            table2[i] = current;
            current = current->next??
        }
    }
    

}

bool HashTable::insert(const string &name)
{
    
    return !find(name);
}
