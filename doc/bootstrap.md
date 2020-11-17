### Bootstrap the Blockchain Synchronization

Normally the Kuberbitcoin Core client will download the transaction and network information, called the blockchain, from network by syncing with the other clients. This can be a process that can take multiple days as the Kuberbitcoin block chain has grown to approximately 5 gigabytes, and is growing almost half a gigabyte every month. Luckily there is a safe and fast way to speed up this process. We’ll show you how to bootstrap your blockchain to bring your client up to speed in just a few simple steps.

You only need to do this when first syncing Kuberbitcoin Core; after that, updates are relatively small and shouldn't take too long.

### Requirements

- A fresh install of the Kuberbitcoin Core client software.

### Download the block chain

WIP

#### US Mirror

WIP

#### EU Mirror

WIP

### Importing the blockchain
Launch the Kuberbitcoin Core client once before continuing the process and then exit the Kuberbitcoin Core software. Be sure not to have an actively used wallet in use. Now we are going to copy the download of the blockchain to the Kuberbitcoin Core data directory. You should run the client software at least once so it can generate the data directory. Copy the downloaded bootstrap.dat file into the Kuberbitcoin data folder.

**For Windows users:**
Open explorer, and type into the address bar:

    %APPDATA%\Roaming\Kuberbitcoin

This will open up the data folder. It should look like the image below. Copy over the bootstrap.dat from your download folder to this directory.
WIP

**For OSX users:**
Open Finder by pressing Press [shift] + [cmd] + [g] and enter:

    ~/Library/Application Support/Kuberbitcoin/

**For Linux users:**
The directory is hidden in your User folder. Go to:

    ~/.kuberbitcoin/

### Importing the blockchain
Now start the Kuberbitcoin Core client software. It should show "Importing blocks from disk" like the image below. 
WIP
Wait until the import finishes. The client will download the last days not covered by the import. Congratulations you have successfully imported the blockchain!

### Is this safe?

Yes, the above method is safe. The download contains only raw block chain data and the client verifies this on import. Do not download the blockchain from unofficial sources, especially if they provide `*.rev` and `*.sst` files. These files are not verified and can contain malicious edits.
